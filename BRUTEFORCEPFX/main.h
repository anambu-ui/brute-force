#pragma once

#define OPENSSL_STATICLIB

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>

#include "openssl/pkcs12.h"
#include "openssl/err.h"
#include "openssl/crypto.h"

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "crypt32.lib")

#include "function/pfx.h"