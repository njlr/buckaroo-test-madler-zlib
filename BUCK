include_defs('//BUCKAROO_DEPS')

cxx_test(
  name = 'test1',
  srcs = [
    'test1.cpp',
  ],
  licenses = [
    'LICENSE',
  ],
  compiler_flags = [
    '-pthread', 
  ], 
  linker_flags = [
    '-lpthread', 
  ], 
  platform_linker_flags = [
    ('linux.*', [ '-lpthread' ]), 
  ], 
  deps = BUCKAROO_DEPS,
)
