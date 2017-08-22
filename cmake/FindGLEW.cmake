if (IRRLICHT_LIBRARIES AND IRRLICHT_INCLUDE_DIRS)
  # in cache already
  set(IRRLICHT_FOUND TRUE)
else (IRRLICHT_LIBRARIES AND IRRLICHT_INCLUDE_DIRS)

  find_path(IRRLICHT_INCLUDE_DIR
    NAMES
      irrlicht.h
    PATHS
      /usr/include
      /usr/include/irrlicht
      /usr/local/include
      /usr/local/include/irrlicht
      /opt/local/include
      /sw/include
  )

  find_library(IRRLICHT_LIBRARY
    NAMES
        Irrlicht
    PATHS
      /usr/lib
      /usr/local/lib
      /opt/local/lib
      /sw/lib
  )

  if (IRRLICHT_LIBRARY)
    set(IRRLICHT_FOUND TRUE)
  endif (IRRLICHT_LIBRARY)

  set(IRRLICHT_INCLUDE_DIRS
    ${IRRLICHT_INCLUDE_DIR}
  )

  if (IRRLICHT_FOUND)
    set(IRRLICHT_LIBRARIES
      ${IRRLICHT_LIBRARIES}
      ${IRRLICHT_LIBRARY}
    )
  endif (IRRLICHT_FOUND)

  if (IRRLICHT_INCLUDE_DIRS AND IRRLICHT_LIBRARIES)
     set(IRRLICHT_FOUND TRUE)
  endif (IRRLICHT_INCLUDE_DIRS AND IRRLICHT_LIBRARIES)

  if (IRRLICHT_FOUND)
    if (NOT IRRLICHT_FIND_QUIETLY)
      message(STATUS "Found Irrlicht: ${IRRLICHT_LIBRARIES}")
    endif (NOT IRRLICHT_FIND_QUIETLY)
  else (IRRLICHT_FOUND)
    if (IRRLICHT_FIND_REQUIRED)
      message(FATAL_ERROR "Could not find Irrlicht")
    endif (IRRLICHT_FIND_REQUIRED)
  endif (IRRLICHT_FOUND)

  # show the IRRLICHT_INCLUDE_DIRS and IRRLICHT_LIBRARIES variables only in the advanced view
  mark_as_advanced(IRRLICHT_INCLUDE_DIRS IRRLICHT_LIBRARIES)

endif (IRRLICHT_LIBRARIES AND IRRLICHT_INCLUDE_DIRS)