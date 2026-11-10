set -x

if [ "$1" = "cert" ]; then
    openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout server.key -out server.crt -subj "/CN=localhost"
elif [ "$1" = "build" ]; then
    docker build -t yura54_https .
elif [ "$1" = "create" ]; then
    pwd    
    docker create -p 80:80 -p 443:443 \
        -v $(pwd)/..:/workspace/yura54 \
        -v $(pwd)/server.crt:/etc/nginx/certs/server.crt \
        -v $(pwd)/server.key:/etc/nginx/certs/server.key \
        --name yura54_https yura54_https:latest
elif [ "$1" = "start" ]; then
    docker start yura54_https 
elif [ "$1" = "stop" ]; then
    docker stop yura54_https 
elif [ "$1" = "login" ]; then
    docker start yura54_https 
    docker exec -it yura54_https bash
fi
