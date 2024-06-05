if [ "$1" == "compile" ]
then
    mkdir -p out
    g++ main.cpp -I/usr/local/Cellar/sfml/2.6.1/include -o out/main -L/usr/local/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system
fi

if [ "$1" == "run" ]
then
    ./out/main
fi