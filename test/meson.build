test_deps = [dependency('gtk+-3.0'), dependency('webkit2gtk-4.0')]
incdirs = include_directories('../src')

test_string = executable('test-string-result-' + api_path,
                         ['testbase.h', 'testbase.c','teststring.c'],
                         dependencies: test_deps,
                         include_directories: incdirs,
                         link_with: libwkjscore)

test_int = executable('test-int-result-' + api_path,
                      ['testbase.h', 'testbase.c', 'testinteger.c'],
                      dependencies: test_deps,
                      include_directories: incdirs,
                      link_with: libwkjscore)

test('Test string retrieval', test_string, is_parallel: false)
test('Test integer retrieval', test_int, is_parallel: false)
