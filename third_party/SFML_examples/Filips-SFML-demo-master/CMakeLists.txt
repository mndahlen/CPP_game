Project(SFML-demo)

message("  v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v ")
message("> Du behöver följande moduler när du kompilerar på IDA's maskiner:")
message("> module add prog/cmake")
message("> module add prog/gcc/6.1.0")
message("> module add prog/sfml-2-gcc-6")
message("> Ovan kommandon har effekt enbart i den terminal där de körs.")
message("  ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ")

cmake_minimum_required(VERSION 3.5)

# Använd C++ 17.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# Ta all upptänklig hjälp från kompilatorn.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++ -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wold-style-cast")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wsuggest-attribute=const")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wsuggest-final-types")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wsuggest-final-methods")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wsuggest-override")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wduplicated-cond")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wzero-as-null-pointer-constant")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wuseless-cast")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconcepts")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual")

# På skolans Linux -system finns två versioner av SFML. Se vilken som används:
if (DEFINED ENV{LOADEDMODULES} AND ("$ENV{LOADEDMODULES}" MATCHES ".*prog/gcc/6.1.0.*"))
  set(CMAKE_CXX_COMPILER /sw/gcc-6.1.0/bin/g++)
  if (DEFINED ENV{SFML_ROOT})
    list(APPEND CMAKE_MODULE_PATH "$ENV{SFML_ROOT}/share/SFML/cmake/Modules")
  endif()
endif()

# Välj vilka delar av SFML som ska användas.
set(SFML_MODULES network graphics window system)

# Försök att hitta SFML genom att anropa 'FindSFML.cmake '.
find_package(SFML 2 COMPONENTS ${SFML_MODULES})
include_directories(${SFML_INCLUDE_DIR})

# Om det inte gick hoppas vi att det är installerat i alla fall.
if (NOT (${SFML_FOUND} STREQUAL "TRUE"))
  message("SFML not found, using fallback guesses")
  set(SFML_LIBRARIES "")
  foreach(i ${SFML_MODULES})
    list(APPEND SFML_LIBRARIES "sfml-${i}")
  endforeach(i)
endif()

# Ange källfiler, lägg till de filer som ni behöver!
set(SOURCE_FILES shooter.cpp)

# Säg till CMake att skapa en körbar fil som heter 'sfml '.
add_executable(shooter ${SOURCE_FILES})

# Länka med biblioteken som vi hittade tidigare.
target_link_libraries(shooter ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
