FROM node:22-bookworm

WORKDIR /app

RUN apt-get update \
    && apt-get install -y g++ \
    && rm -rf /var/lib/apt/lists/*

COPY backend/include ./backend/include
COPY backend/src ./backend/src
COPY backend/node/package.json ./backend/node/package.json
COPY backend/node/server.js ./backend/node/server.js
COPY frontend ./frontend

WORKDIR /app/backend/node

RUN npm install

RUN g++ -std=c++17 \
    ../src/ApiServer.cpp \
    ../src/NetworkAPI.cpp \
    ../src/Graph.cpp \
    ../src/BFS.cpp \
    ../src/Dijkstra.cpp \
    ../src/BellmanFord.cpp \
    ../src/RouteScore.cpp \
    ../src/MetricNormalizer.cpp \
    ../src/BalancedRouting.cpp \
    -I../include \
    -o api_server

EXPOSE 3000

CMD ["node", "server.js"]