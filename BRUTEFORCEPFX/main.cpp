#include "main.h"


int main() {
    std::string pfxFile = "C:\\cert\\certificate.pfx";
    std::string charset = "qwertyuiopasdfghjklzxcvbnm1234567890QWERTYUIOPASDFGHJKLZXCVBNM";
    int maxLength = 12;

    bruteForcePfx(pfxFile, charset, maxLength);
    system("Pause");
    return 0;
}
