{
  "cmd": ["bash", "-c", 
          "g++ -std=c++14 '${file}' -o x && ./x" ],
  "file_regex": 
        "^(..[^:]*):([0-9]+):?([0-9]+)?:? (.*)$",
  "working_dir": "${file_path}",
  "selector": "source.c, source.c++",
  "variants":
  [
    {
      "name": "Run",
      "cmd": ["bash", "-c", 
            "g++ -std=c++14 '${file}' -o x && ./x"]
    }
  ]
}
// -Wextra -O2 -Wl,--stack=268435456 -Wfloat-equal 
// -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -Wall
