/*
 *  This file is part of TYSS.
 *  Copyright (C) 2024-2026 R-YaTian
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

#include <string>
#include <vector>
#include <algorithm>
#include <curl/curl.h>

#include "drive/curlhelper.h"

size_t CurlHelper::writeDataString(const char *buff, size_t sz, size_t cnt, void *u)
{
    std::string *str = (std::string *)u;
    str->append(buff, 0, sz * cnt);
    return sz * cnt;
}

size_t CurlHelper::writeHeaders(const char *buff, size_t sz, size_t cnt, void *u)
{
    std::vector<std::string> *headers = (std::vector<std::string> *)u;
    headers->push_back(buff);
    return sz * cnt;
}

size_t CurlHelper::readDataFile(char *buff, size_t sz, size_t cnt, void *u)
{
    FILE *in = (FILE *)u;
    return fread(buff, sz, cnt, in);
}

size_t CurlHelper::writeDataFile(const char *buff, size_t sz, size_t cnt, void *u)
{
    FILE *f = (FILE *)u;
    return fwrite(buff, sz, cnt, f);
}

static void stripChar(char _c, std::string& _s)
{
    _s.erase(std::remove(_s.begin(), _s.end(), _c), _s.end());
}

std::string CurlHelper::getHeader(const std::string& name, std::vector<std::string> *h)
{
    std::string ret = HEADER_ERROR;
    for (unsigned i = 0; i < h->size(); i++)
    {
        std::string curHeader = h->at(i);
        size_t colonPos = curHeader.find_first_of(':');
        if (curHeader.substr(0, colonPos) == name)
        {
            ret = curHeader.substr(colonPos + 2);
            break;
        }
    }
    stripChar('\n', ret);
    stripChar('\r', ret);
    return ret;
}
