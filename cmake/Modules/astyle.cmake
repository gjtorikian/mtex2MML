# Find the program
find_program(ASTYLE_EXECUTABLE astyle DOC "A tool to format the code")

# Add a custom target
add_custom_target("format" COMMAND
  "${ASTYLE_EXECUTABLE}"
  --indent=spaces=2 --style=1tbs --keep-one-line-blocks
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.c
  VERBATIM
)
