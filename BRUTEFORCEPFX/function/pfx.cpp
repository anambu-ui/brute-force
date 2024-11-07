#include "../main.h"

bool trykey(const std::string& pfxFile, const std::string& key) {
    FILE* file = nullptr;
    errno_t err = fopen_s(&file, pfxFile.c_str(), "rb");
    if (err != 0 || !file) {
        std::cerr << "Unable to open file: " << pfxFile << std::endl;
        return false;
    }

    PKCS12* p12 = d2i_PKCS12_fp(file, NULL);
    fclose(file);

    if (!p12) {
        std::cerr << "Error reading file." << std::endl;
        return false;
    }

    EVP_PKEY* pkey = nullptr;
    X509* cert = nullptr;
    STACK_OF(X509)* ca = nullptr;

    int result = PKCS12_parse(p12, key.c_str(), &pkey, &cert, &ca);
    PKCS12_free(p12);

    if (result) {
        if (pkey) EVP_PKEY_free(pkey);
        if (cert) X509_free(cert);
        if (ca) sk_X509_free(ca);
        return true;
    }
    else {
        return false;
    }
}

void bruteForcePfx(const std::string& pfxFile, const std::string& charset, int maxLength) {
    std::string key(maxLength, ' ');

    for (int length = 1; length <= maxLength; ++length) {
        key.assign(length, charset[0]);

        while (true) {
            //            std::cout << "Trying key: " << key << std::endl;

            if (trykey(pfxFile, key)) {
                std::cout << "Success! key found: " << key << std::endl;
                return;
            }

            for (int i = length - 1; i >= 0; --i) {
                auto pos = charset.find(key[i]);
                if (pos < charset.size() - 1) {
                    key[i] = charset[pos + 1];
                    break;
                }
                else {
                    key[i] = charset[0];
                    if (i == 0) {
                        if (length == maxLength) {
                            std::cout << "key not found." << std::endl;
                            return;
                        }
                    }
                }
            }

            if (key[0] == charset[0] && key.substr(1) == std::string(length - 1, charset[0])) {
                break;
            }
        }
    }
}