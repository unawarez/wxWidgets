/////////////////////////////////////////////////////////////////////////////
// Name:        xlocale.h
// Purpose:     interface of wxXLocale
// Author:      wxWidgets team
// RCS-ID:      $Id$
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////


/**
    @class wxXLocale

    This class represents a locale object used by so-called xlocale API.

    Unlike wxLocale it doesn't provide any non-trivial operations but simply
    provides a portable wrapper for POSIX @c locale_t type.

    It exists solely to be provided as an argument to various @c wxFoo_l() functions
    which are the extensions of the standard locale-dependent functions (hence the
    name xlocale). These functions do exactly the same thing as the corresponding
    standard @c foo() except that instead of using the global program locale
    they use the provided wxXLocale object.

    For example, if the user runs the program in French locale, the standard
    @c printf() function will output floating point numbers using decimal comma
    instead of decimal period. If the program needs to format a floating-point
    number in a standard format it can use:
    @code wxPrintf_l(wxXLocale::GetCLocale(), "%g", number) @endcode
    to do it.

    Conversely, if a program wanted to output the number in French locale, even if
    the current locale is different, it could use wxXLocale(wxLANGUAGE_FRENCH).


    @section xlocale_avail Availability

    This class is fully implemented only under the platforms where xlocale POSIX
    API or equivalent is available. Currently the xlocale API is available under
    most of the recent Unix systems (including Linux, various BSD and Mac OS X) and
    Microsoft Visual C++ standard library provides a similar API starting from
    version 8 (Visual Studio 2005).

    If neither POSIX API nor Microsoft proprietary equivalent are available, this
    class is still available but works in degraded mode: the only supported locale
    is the C one and attempts to create wxXLocale object for any other locale will
    fail. You can use the preprocessor macro @c wxHAS_XLOCALE_SUPPORT to test if
    full xlocale API is available or only skeleton C locale support is present.

    Notice that wxXLocale is new in wxWidgets 2.9.0 and is not compiled in if
    @c wxUSE_XLOCALE was set to 0 during the library compilation.


    @section xlocale_func Locale-dependent functions

    Currently the following @c _l-functions are available:
    - Character classification functions:
      @c wxIsxxx_l(), e.g. @c wxIsalpha_l(), @c wxIslower_l() and all the others.
    - Character transformation functions:
      @c wxTolower_l() and @c wxToupper_l()
    We hope to provide many more functions (covering numbers, time and formatted
    IO) in the near future.

    @library{wxbase}
    @category{misc}

    @see wxLocale
*/
class wxXLocale
{
public:
    /**
        Creates an uninitialized locale object, IsOk() method will return @false.
    */
    wxLocale();

    /**
        Creates the locale object corresponding to the specified language.
    */
    wxLocale(wxLanguage lang);

    /**
        Creates the locale object corresponding to the specified locale string.
        The locale string is system-dependent, use constructor taking wxLanguage
        for better portability.
    */
    wxLocale(const char* loc);

    /**
        Returns the global object representing the "C" locale.
        For an even shorter access to this object a global @c wxCLocale variable
        (implemented as a macro) is provided and can be used instead of calling
        this method.
    */
    static wxXLocale& GetCLocale();

    /**
        Returns @true if this object is initialized, i.e. represents a valid locale
        or @false otherwise.
    */
    bool IsOk() const;
};
