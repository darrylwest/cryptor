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
            /bin/rm -f bin/unit bin/cryptor
        
            shift
        ;;
        run)
            cd bin && ./cryptor

            shift
        ;;
        watch)
            watchexec -c -w src/ -w include/ -e h,hpp,cpp ./mk test

            exit 0
        ;;
        test)
            cd bin/ && ./unit

            shift
        ;;
        help)
            echo "Targets:"
            echo ""
            echo "   build   : compile cryptor and unit tests"
            echo "   test    : run all tests"
            echo "   run     : runs the app and shows version"
            echo "   watch   : run watcher over source and include"
            echo "   clean   : remove binary builds"
            echo "   help    : show this help"
            
            exit 0
        ;;

        build)
            cd src && pwd && make && make unit

            shift
        ;;

    esac
done


