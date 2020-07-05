FIND_PATH(JSONCPP_INCLUDE_DIR NAMES
  allocator.h
  assertions.h
  autolink.h
  config.h
  forwards.h
  json.h
  json_features.h
  reader.h
  value.h
  version.h
  writer.h
  PATH_SUFFIXES json jsoncpp/json)
MARK_AS_ADVANCED(JSONCPP_INCLUDE_DIR)
 
FIND_LIBRARY(JSONCPP_LIBRARY NAMES
  jsoncpp
  libjsoncpp
  jsoncpplib)
MARK_AS_ADVANCED(JSONCPP_LIBRARY)
 
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS (JsonCpp DEFAULT_MSG
                                   JSONCPP_LIBRARY JSONCPP_INCLUDE_DIR)
