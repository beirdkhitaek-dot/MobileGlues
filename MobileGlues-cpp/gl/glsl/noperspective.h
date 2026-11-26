// MobileGlues - gl/glsl/noperspective.h
// SPDX-License-Identifier: LGPL-2.1-only
// End of Source File Header
#ifndef MOBILEGLUES_NOPERSPECTIVE_H
#define MOBILEGLUES_NOPERSPECTIVE_H

#include <string>

// Removes the `noperspective` qualifier and any
// `#extension GL_NV_shader_noperspective_interpolation` directive, for drivers
// without that extension. Varyings then use the default (smooth) interpolation.
// Comments are left alone and line numbers are preserved.
std::string strip_noperspective(const std::string& source);

#endif // MOBILEGLUES_NOPERSPECTIVE_H
