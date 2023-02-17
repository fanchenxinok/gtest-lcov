#! /bin/bash
cd ..
make clean
cd ./gtest_lcov
make clean
sudo rm -rf ./lcov_out/*
make
./appMain --gtest_output="xml:output.xml"

##  参数-d 后面跟的目录是.gcon .gcda 所在的根目录
lcov-1.11/bin/lcov -d ../ -t 'appMain' -o 'appMain.info' -b . -c
#/home/fanchenxin/tools/lcov-1.11/bin/lcov -d ../ -t 'appMain' -o 'appMain.info' -b . -c
#/home/fanchenxin/tools/lcov-1.11/bin/lcov --directory . --output-file test_case.info --test-name  test_case

#去除不关心的文件覆盖率信息，比如头文件
lcov-1.11/bin/lcov -r appMain.info '*.h' '/usr/include/*' -o appMain.info

#../lcov-1.11/bin/genhtml -o . test_case.info
#/home/fanchenxin/tools/lcov-1.11/bin/genhtml appMain.info --quiet --output-directory lcov_out --title "appMain"
lcov-1.11/bin/genhtml appMain.info --quiet --output-directory lcov_out --title "appMain" 

#gtest test report
xsltproc ./gtest2html/gtest2html.xslt output.xml > gtest_unittest.html

firefox ./lcov_out/index.html

#--show-details

# --capture --legend
