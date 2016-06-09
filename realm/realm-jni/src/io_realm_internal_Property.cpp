#include "io_realm_internal_Property.h"
#include "util.hpp"

#include "property.hpp"

#include <assert.h>

using namespace realm;

#define ENUM_VALUE_MISMATCH_MSG "Enum values mismatch."
static_assert(io_realm_internal_Property_PROPERTY_TYPE_INT == static_cast<jint>(PropertyType::Int),
        ENUM_VALUE_MISMATCH_MSG);
static_assert(io_realm_internal_Property_PROPERTY_TYPE_BOOL == static_cast<jint>(PropertyType::Bool),
        ENUM_VALUE_MISMATCH_MSG);
static_assert(io_realm_internal_Property_PROPERTY_TYPE_FLOAT == static_cast<jint>(PropertyType::Float),
        ENUM_VALUE_MISMATCH_MSG);
static_assert(io_realm_internal_Property_PROPERTY_TYPE_DOUBLE == static_cast<jint>(PropertyType::Double),
        ENUM_VALUE_MISMATCH_MSG);
static_assert(io_realm_internal_Property_PROPERTY_TYPE_STRING == static_cast<jint>(PropertyType::String),
        ENUM_VALUE_MISMATCH_MSG);
static_assert(io_realm_internal_Property_PROPERTY_TYPE_DATA == static_cast<jint>(PropertyType::Data),
        ENUM_VALUE_MISMATCH_MSG);
static_assert(io_realm_internal_Property_PROPERTY_TYPE_ANY == static_cast<jint>(PropertyType::Any),
        ENUM_VALUE_MISMATCH_MSG);
static_assert(io_realm_internal_Property_PROPERTY_TYPE_DATE == static_cast<jint>(PropertyType::Date),
        ENUM_VALUE_MISMATCH_MSG);
static_assert(io_realm_internal_Property_PROPERTY_TYPE_OBJECT == static_cast<jint>(PropertyType::Object),
        ENUM_VALUE_MISMATCH_MSG);
static_assert(io_realm_internal_Property_PROPERTY_TYPE_ARRAY == static_cast<jint>(PropertyType::Array),
        ENUM_VALUE_MISMATCH_MSG);

jlong JNICALL Java_io_realm_internal_Property_nativeCreate
(JNIEnv *env, jclass, jstring jname, jint type, jstring jobject_type, jboolean is_primary, jboolean is_indexed, jboolean is_nullable) {
    try {
        JStringAccessor name(env, jname); // throws
        JStringAccessor object_type(env, jobject_type); // throws
        Property *property = new Property(name, static_cast<PropertyType>(type), object_type, is_primary, is_indexed, is_nullable);
        return reinterpret_cast<jlong>(property);
    } CATCH_STD ()

    return reinterpret_cast<jlong>(nullptr);
}

void JNICALL Java_io_realm_internal_Property_nativeClose
(JNIEnv *, jclass, jlong native_ptr) {
    TR_ENTER_PTR(native_ptr)
    delete PROPERTY(native_ptr);
}

jstring JNICALL Java_io_realm_internal_Property_nativeGetName
(JNIEnv *env, jclass, jlong native_ptr) {
    TR_ENTER_PTR(native_ptr)
    try {
        return to_jstring(env, PROPERTY(native_ptr)->name);
    } CATCH_STD()

    return NULL;
}

jint JNICALL Java_io_realm_internal_Property_nativeGetType
(JNIEnv *, jclass, jlong native_ptr) {
    TR_ENTER_PTR(native_ptr)
    return static_cast<jint>(PROPERTY(native_ptr)->type);
}

jstring JNICALL Java_io_realm_internal_Property_nativeGetObjectType
(JNIEnv *env, jclass, jlong native_ptr) {
    TR_ENTER_PTR(native_ptr)
    try {
        return to_jstring(env, PROPERTY(native_ptr)->object_type);
    } CATCH_STD()

    return NULL;
}

jboolean JNICALL Java_io_realm_internal_Property_nativeIsPrimary
(JNIEnv *, jclass, jlong native_ptr) {
    TR_ENTER_PTR(native_ptr)
    return PROPERTY(native_ptr)->is_primary;
}

jboolean JNICALL Java_io_realm_internal_Property_nativeIsIndexed
(JNIEnv *, jclass, jlong native_ptr) {
    TR_ENTER_PTR(native_ptr)
    return PROPERTY(native_ptr)->is_indexed;
}

jboolean JNICALL Java_io_realm_internal_Property_nativeIsNullable
(JNIEnv *, jclass, jlong native_ptr) {
    TR_ENTER_PTR(native_ptr)
    return PROPERTY(native_ptr)->is_nullable;
}

