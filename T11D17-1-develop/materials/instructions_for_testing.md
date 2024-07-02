# Instructions for running tests.

In addition to testing for correct output data, the autotest system will
check your program and its source code for the following points:

* **Style tests.** To check how much the beauty of your code matches
  for example, you can test your code using the _clang-format_ utility.
  The ```materials/linters``` folder contains the ```.clang-format``` file, which contains
  the necessary settings for the style test. This configuration file extends its action to all files that lie with it in the directory
  or in the directories below. So in order for these settings to apply to your source code files,
  copy ```.clang-format``` to the ```src``` folder. \
  \
  To run the style check, run the following command: \
  ```clang-format -n src/sourcefile_name.c``` 

  Required version of clang-format: \
  **Mac** 14.0.5 \
  **Linux** 13.0.1

* **Test for correct operation with memory.** When writing C programs, it is very important to watch for memory leaks. To do this the _valgrind_ utility is quite often used in Unix-like operating systems. However OS X has some troubles with valgrind support, so it is possible to use _leaks_ utility instead. Go into we will not discuss the mechanism of their operation now - if you are interested, you can read about it on Google.

 #### _LEAKS (MacOS)_

  **Important!** If you are using a Unix-like system (for example, Ubuntu / Linux Mint / Debian), go to the [section with instructions for using VALGRIND](#valgrind-ubuntu--linux-mint--debian).

  To run your executable file using this utility, type in the terminal: \
  ```leaks -atExit -- ./main.out | grep LEAK:```  
  
  Pay your attention that there is ```| grep LEAK:``` command. We use it to short leaks output to see only lines with leaks if they are there. If you want to see the whole output, just remove this command.  
  
  When you run your executable file using _leaks_ you may see an error:  
  >dyld: could not load inserted library ‘/usr/local/lib/libLeaksAtExit.dylib’ because image not found
  
  It’s because _leaks_ did not find _libLeaksAtExit.dylib_ library. \
  You need to type the following commands in this case.   
  ```sh
  cd /usr/local/lib  
  sudo ln -s /Applications/Xcode.app/Contents/Developer/usr/lib/libLeaksAtExit.dylib
  ```

  _Additionally:_  \
  Use the ```-exclude``` option of _leaks_ to filter out leaks in functions with known memory leaks. 
  This option helps reduce the amount of extra information reported by _leaks_.

  ---

  #### _VALGRIND (Ubuntu / Linux Mint / Debian)_

   To run your executable file using this utility, type in the terminal: \
   ```valgrind --tool=memcheck --leak-check=yes. /main. out```

   It is strongly recommended not to use _valgrind_ utility in OS X, use [_leaks_](#leaks-macos) utility  instead.

  Also, you can read the [information on installing the software and Valgrind](https://21-school.ru/install_soft_to_school_IMacs).
  
* **Static code analysis.** Sometimes (or not quite sometimes) it happens that
  a correctly compiled C program runs completely incorrectly or terminates
  with an error trying to access the wrong memory area. To prevent this from happening
  errors at the stage of writing the program, use special utilities that analyze
  check your source code for potential errors. Our autotest system uses
  ```cppcheck``` for this.

  You can test your source code: \
  ```cppcheck --enable=all --suppress=missingIncludeSystem src/soursefile_name.c``` \
  You can also check all the source code files in the directory at once: \
  ```cppcheck --enable=all --suppress=missingIncludeSystem src/```

  Required version of clang-format: \
  **Mac** 2.8 \
  **Linux** 2.8
