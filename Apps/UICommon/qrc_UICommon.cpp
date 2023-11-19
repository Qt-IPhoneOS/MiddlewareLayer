/****************************************************************************
** Resource object code
**
** Created by: The Resource Compiler for Qt version 6.6.0
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

static const unsigned char qt_resource_data[] = {
  // /home/thaivodinh/Desktop/MY_PROJECT/Qt-IPhoneOS/IPhoneOS/Apps/UICommon/Components/Common.qml
  0x0,0x0,0x0,0x1f,
  0x69,
  0x6d,0x70,0x6f,0x72,0x74,0x20,0x51,0x74,0x51,0x75,0x69,0x63,0x6b,0x20,0x32,0x2e,
  0x31,0x35,0xa,0xa,0x49,0x74,0x65,0x6d,0x20,0x7b,0xa,0xa,0x7d,0xa,
  
};

static const unsigned char qt_resource_name[] = {
  // Components
  0x0,0xa,
  0x7,0x6e,0x9,0x33,
  0x0,0x43,
  0x0,0x6f,0x0,0x6d,0x0,0x70,0x0,0x6f,0x0,0x6e,0x0,0x65,0x0,0x6e,0x0,0x74,0x0,0x73,
    // Common.qml
  0x0,0xa,
  0x4,0x68,0x1c,0xbc,
  0x0,0x43,
  0x0,0x6f,0x0,0x6d,0x0,0x6d,0x0,0x6f,0x0,0x6e,0x0,0x2e,0x0,0x71,0x0,0x6d,0x0,0x6c,
  
};

static const unsigned char qt_resource_struct[] = {
  // :
  0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x1,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  // :/Components
  0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x2,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  // :/Components/Common.qml
  0x0,0x0,0x0,0x1a,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,
0x0,0x0,0x1,0x8b,0xc9,0xa6,0xdf,0xf4,

};

#ifdef QT_NAMESPACE
#  define QT_RCC_PREPEND_NAMESPACE(name) ::QT_NAMESPACE::name
#  define QT_RCC_MANGLE_NAMESPACE0(x) x
#  define QT_RCC_MANGLE_NAMESPACE1(a, b) a##_##b
#  define QT_RCC_MANGLE_NAMESPACE2(a, b) QT_RCC_MANGLE_NAMESPACE1(a,b)
#  define QT_RCC_MANGLE_NAMESPACE(name) QT_RCC_MANGLE_NAMESPACE2( \
        QT_RCC_MANGLE_NAMESPACE0(name), QT_RCC_MANGLE_NAMESPACE0(QT_NAMESPACE))
#else
#   define QT_RCC_PREPEND_NAMESPACE(name) name
#   define QT_RCC_MANGLE_NAMESPACE(name) name
#endif

#ifdef QT_NAMESPACE
namespace QT_NAMESPACE {
#endif

bool qRegisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);
bool qUnregisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);

#ifdef QT_NAMESPACE
}
#endif

int QT_RCC_MANGLE_NAMESPACE(qInitResources_UICommon)();
int QT_RCC_MANGLE_NAMESPACE(qInitResources_UICommon)()
{
    int version = 3;
    QT_RCC_PREPEND_NAMESPACE(qRegisterResourceData)
        (version, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

int QT_RCC_MANGLE_NAMESPACE(qCleanupResources_UICommon)();
int QT_RCC_MANGLE_NAMESPACE(qCleanupResources_UICommon)()
{
    int version = 3;
    QT_RCC_PREPEND_NAMESPACE(qUnregisterResourceData)
       (version, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

#ifdef __clang__
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

namespace {
   struct initializer {
       initializer() { QT_RCC_MANGLE_NAMESPACE(qInitResources_UICommon)(); }
       ~initializer() { QT_RCC_MANGLE_NAMESPACE(qCleanupResources_UICommon)(); }
   } dummy;
}

#ifdef __clang__
#   pragma clang diagnostic pop
#endif
