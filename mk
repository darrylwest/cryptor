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
        init)
            /bin/rm -fr build/
            cmake -Bbuild .

            shift
        ;;
        build)
            clear

            cmake --build build/ 
            $root/build/cryptor --version
            # $root/build/unit


            shift
        ;;
        unit)
            $root/build/unit

            shift
        ;;
        test)
            # TODO check that unit has been built and is newer that all the souces
            # $root/build/unit
            $root/build/integration
            bat --paging=never $root/service.log

            shift
        ;;
        run)
            # TODO check that cryptor has been built and is newer that all the souces
            $root/build/cryptor --base $root/html

            shift
        ;;
        run-debug)
            # TODO check that cryptor has been built and is newer that all the souces
            $root/build/cryptor --base $root/html --level 0

            shift
        ;;
        clean)
            /bin/rm -f $root/build/cryptor $root/build/unit
        
            shift
        ;;
        clobber)
            /bin/rm -fr build/

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
        version)
            curl -k https://localhost:$port/version

            shift
        ;;


        help)
            echo "Targets:"
            echo ""
            echo "   build    : compile and run cryptor and unit tests"
            echo "   test     : run all tests"
            echo "   run      : runs the app and shows version"
            echo "   run-debug: runs the service with logging set to debug"
            echo "   watch    : run watcher over source and include"
            echo "   clean    : remove binary builds"
            echo "   clobber  : remove the entire build folder"
            echo "   show     : runs curl against localhost to view index page"
            echo "   shutdown : runs localhost curl shutdown the server"
            echo "   help     : show this help"
            
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


