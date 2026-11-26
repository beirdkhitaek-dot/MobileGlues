// MobileGlues - gl/glsl/noperspective.cpp
// SPDX-License-Identifier: LGPL-2.1-only
// End of Source File Header

#include "noperspective.h"

#include <cctype>

static bool is_ident(char c) {
    return std::isalnum(static_cast<unsigned char>(c)) || c == '_';
}

// True if `line` is `# extension GL_NV_shader_noperspective_interpolation ...`
static bool is_noperspective_extension(const std::string& line) {
    size_t p = line.find_first_not_of(" \t");
    if (p == std::string::npos || line[p] != '#') return false;
    p = line.find_first_not_of(" \t", p + 1);
    if (p == std::string::npos || line.compare(p, 9, "extension") != 0) return false;
    p = line.find_first_not_of(" \t", p + 9);
    const std::string name = "GL_NV_shader_noperspective_interpolation";
    if (p == std::string::npos || line.compare(p, name.size(), name) != 0) return false;
    p += name.size();
    return p >= line.size() || !is_ident(line[p]);
}

std::string strip_noperspective(const std::string& source) {
    if (source.find("noperspective") == std::string::npos) return source;

    std::string out;
    out.reserve(source.size());
    bool in_block_comment = false;
    size_t i = 0;
    const size_t n = source.size();

    while (i < n) {
        if (!in_block_comment && (i == 0 || source[i - 1] == '\n')) {
            size_t end = source.find('\n', i);
            if (end == std::string::npos) end = n;
            if (is_noperspective_extension(source.substr(i, end - i))) {
                i = end; // keep the newline so line numbers do not shift
                continue;
            }
        }

        if (in_block_comment) {
            if (source.compare(i, 2, "*/") == 0) {
                out += "*/";
                i += 2;
                in_block_comment = false;
            } else {
                out += source[i++];
            }
        } else if (source.compare(i, 2, "/*") == 0) {
            out += "/*";
            i += 2;
            in_block_comment = true;
        } else if (source.compare(i, 2, "//") == 0) {
            size_t end = source.find('\n', i);
            if (end == std::string::npos) end = n;
            out.append(source, i, end - i);
            i = end;
        } else if (is_ident(source[i])) {
            size_t end = i;
            while (end < n && is_ident(source[end]))
                ++end;
            if (source.compare(i, end - i, "noperspective") != 0) out.append(source, i, end - i);
            i = end;
        } else {
            out += source[i++];
        }
    }
    return out;
}
