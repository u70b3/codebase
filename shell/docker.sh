 #!/usr/bin/env bash
 
SERVER="tars"
BASEURL="csighub.tencentyun.com/sppd_wh"
IMAGE="tars_4.8_dev:2.4.14"
LOCAL_CODE_DIR="/root/shared"
IMAGE_CODE_DIR="/root/shared"

FULL_IMAGE="${BASEURL}/${IMAGE}"

pull() {
    echo "pulling image ${BASEURL}/${IMAGE}"
    docker pull "${BASEURL}/${IMAGE}"
}

run() {
    docker run -it -v ${LOCAL_CODE_DIR}:${IMAGE_CODE_DIR} --net=host --privileged --name=${SERVER} ${FULL_IMAGE} /bin/bash
}

start() {
    docker start ${SERVER}
}

stop() {
    docker stop ${SERVER}
}

attach() {
    docker attach ${SERVER}
}

exec() {
    docker exec -it --user root ${SERVER} /bin/bash
}

clean() {
    local choice="N"
    read -p "Attention! You're removing the docker ${SERVER}, choose [y/N]" choice
    if [[ ${choice} = "Y" || ${choice} = "y" || ${choice} = "yes" ]]
    then
        echo "Now removing docker ${SERVER}!"
        docker rm ${SERVER}
    else
        echo "Cancel removing..."
        exit -1
    fi
}

rmi() {
    local choice="N"
    read -p "Attention! You're removing the image ${IMAGE}, choose [y/N]" choice
    if [[ $choice = "Y" || $choice = "y" || $choice = "yes" ]]
    then
        echo "Now removing image ${IMAGE}!"
        docker rmi ${FULL_IMAGE}
    else
        echo "Cancel removing..."
        exit -1
    fi
}

usage() {
    echo "Usage: bash docker.sh pull|run|start|stop|attach|clean|rmi"
}

if [ $# -lt 1 ];
then
    usage
    exit -1
fi

case $1 in
        pull)
            pull
        ;;
        run)
            run
        ;;
        start)
            start
        ;;
        stop)
            stop
        ;;
        attach)
            attach
        ;;
        exec)
            exec 
        ;;
        clean)
            clean
        ;;
        rmi)
            rmi
        ;;
        end)
            echo "stop something"
        ;;
        *)
            echo "unknown cmd $1"
            usage
        ;;
esac
