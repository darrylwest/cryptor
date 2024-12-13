#!/usr/bin/env bash
#
# dpw@plaza.localdomain | 2024-12-13 03:28:43
#
#

set -eu

# parse the cli
while [[ $# -gt 0 ]]
do
    case $1 in
        clean)
            cmake --build build --target clean
        
            shift
        ;;
        run)
            cmake --build build
            ./build/standalone/${PROJECT} --version

            shift
        ;;
        watch)
            watchexec -c -w standalone/source -w source/ -w test/source/ -w include/ -e h,hpp,cpp ./mk test

            exit 0
        ;;
        test)
            cmake --build build/test
            ./build/test/${PROJECT}Tests

            shift
        ;;
        help)
            echo "Targets:"
            echo ""
            echo "   test    : compile and run all tests"
            echo "   run     : runs the app and shows version"
            echo "   watch   : run watcher over source and include"
            echo "   clean   : remove binary builds"
            echo "   help    : show this help"
            
            exit 0
        ;;

        *)
            cmake --build build

            shift
        ;;
    esac
done


