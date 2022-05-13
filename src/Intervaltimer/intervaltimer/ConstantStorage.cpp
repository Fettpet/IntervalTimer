#include "ConstantStorage.h"

ConstantStorage* ConstantStorage::instance = nullptr;

ConstantStorage* ConstantStorage::create(QQmlEngine* qmlEngine, QJSEngine* jsEngine) {
    if (instance == nullptr) {
        instance = new ConstantStorage();
    }
    return instance;
}

int ConstantStorage::getProjectVersionPatch() const {
#ifdef CMAKE_PROJECT_VERSION_PATCH
    return CMAKE_PROJECT_VERSION_PATCH;
#else
    return 0;
#endif
}

int ConstantStorage::getProjectVersionMinor() const {
#ifdef CMAKE_PROJECT_VERSION_MINOR
    return CMAKE_PROJECT_VERSION_MINOR;
#else
    return 0;
#endif
}

int ConstantStorage::getProjectVersionMajor() const {
#ifdef CMAKE_PROJECT_VERSION_MAJOR
    return CMAKE_PROJECT_VERSION_MAJOR;
#else
    return 0;
#endif
}
