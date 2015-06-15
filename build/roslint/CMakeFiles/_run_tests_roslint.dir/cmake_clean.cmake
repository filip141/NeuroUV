FILE(REMOVE_RECURSE
  "CMakeFiles/_run_tests_roslint"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/_run_tests_roslint.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
