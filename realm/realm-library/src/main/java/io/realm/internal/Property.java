/*
 * Copyright 2016 Realm Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package io.realm.internal;

import java.io.Closeable;
import java.io.IOException;

import io.realm.RealmFieldType;

public class Property implements Closeable {

    public final static int PROPERTY_TYPE_INT = 0;
    public final static int PROPERTY_TYPE_BOOL = 1;
    public final static int PROPERTY_TYPE_FLOAT = 9;
    public final static int PROPERTY_TYPE_DOUBLE = 10;
    public final static int PROPERTY_TYPE_STRING = 2;
    public final static int PROPERTY_TYPE_DATA = 4;
    public final static int PROPERTY_TYPE_ANY = 6;
    public final static int PROPERTY_TYPE_DATE = 8;
    public final static int PROPERTY_TYPE_OBJECT = 12;
    public final static int PROPERTY_TYPE_ARRAY = 13;

    private long nativePtr;

    // FIXME: Check this. We might never need it or we should use clone constructor
    Property(long ptr) {
        nativePtr = ptr;
    }

    public Property(String name, RealmFieldType type, String objectType, boolean isPrimary,
                    boolean isIndexed, boolean isNullable) {
       nativePtr = nativeCreate(name, type.getNativeValue(), objectType, isPrimary, isIndexed, isNullable);
    }

    public String getName() {
        return nativeGetName(nativePtr);
    }

    public RealmFieldType getType() {
        return RealmFieldType.fromNativeValue(nativeGetType(nativePtr));
    }

    public  String getObjectType() {
        return nativeGetObjectType(nativePtr);
    }

    public  boolean isPrimary() {
        return nativeIsPrimary(nativePtr);
    }

    public  boolean isIndexed() {
        return nativeIsIndexed(nativePtr);
    }

    public  boolean isNullable() {
        return nativeIsNullable(nativePtr);
    }

    @Override
    public void close() throws IOException {
        nativeClose(nativePtr);
    }

    @Override
    // Use finalize for now until we find a better way
    protected void finalize() throws Throwable {
        super.finalize();
        if (nativePtr != 0) {
            close();
        }
    }

    private static native long nativeCreate(String name, int type, String objectType, boolean isPrimary,
                                            boolean isIndexed, boolean isNullable);
    private static native void nativeClose(long ptr);
    private static native String nativeGetName(long ptr);
    private static native int nativeGetType(long ptr);
    private static native String nativeGetObjectType(long ptr);
    private static native boolean nativeIsPrimary(long ptr);
    private static native boolean nativeIsIndexed(long ptr);
    private static native boolean nativeIsNullable(long ptr);
}
