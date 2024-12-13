#!/usr/bin/env bash
#
# dpw@plaza.localdomain | 2024-12-13 03:28:43
#
#

set -eu

export root=`pwd`

port=2022

# parse the cli
while [[ $# -gt 0 ]]
do
    case $1 in
        build)
            clear
            cd $root/src/ && make cryptor unit && cd
            cd $root/bin/ && ./cryptor --version && ./unit

            shift
        ;;
        test)
            # TODO check that unit has been built and is newer that all the souces
            cd $root/bin/ && ./unit

            shift
        ;;
        run)
            # TODO check that cryptor has been built and is newer that all the souces
            cd $root/bin/ && ./cryptor --base ../html

            shift
        ;;
        clean)
            /bin/rm -f $root/bin/unit $root/bin/cryptor
        
            shift
        ;;
        watch)
            watchexec -c -w src/ -w include/ -e h,hpp,cpp ./mk build

            exit 0
        ;;

        shutdown)
            curl -k -XDELETE https://localhost:$port/shutdown

            shift
        ;;

        page)
            curl -k https://localhost:$port

            shift
        ;;

        cmake-all)
            /bin/rm -fr build/
            cmake -Bbuild . && cmake --build build/ 

            shift
        ;;

        help)
            echo "Targets:"
            echo ""
            echo "   build   : compile and run cryptor and unit tests"
            echo "   test    : run all tests"
            echo "   run     : runs the app and shows version"
            echo "   watch   : run watcher over source and include"
            echo "   clean   : remove binary builds"
            echo "   show    : runs curl against localhost to view index page"
            echo "   shutdown: runs localhost curl shutdown the server"
            echo "   help    : show this help"
            
            exit 0
        ;;

        build)
            cd src && pwd && make && make unit

            shift
        ;;
        *)
            ./mk help
            exit 0
        ;;

    esac
done


