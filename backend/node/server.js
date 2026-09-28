const http = require("http");
const { spawn } = require("child_process");
const readline = require("readline");
const path = require("path");
const fs = require("fs");

const PORT = process.env.PORT || 3000;

const frontendDirectory = path.join(
    __dirname,
    "../../frontend"
);
const cppExecutable = path.join(
    __dirname,
    process.platform === "win32"
        ? "api_server.exe"
        : "api_server"
);

const cppProcess = spawn(cppExecutable);

const cppReader = readline.createInterface({
    input: cppProcess.stdout
});

const pendingRequests = [];

cppReader.on("line", (line) => {

    const request = pendingRequests.shift();

    if (!request) {
        return;
    }

    try {
        const response = JSON.parse(line);

        request.resolve(response);
    }
    catch (error) {

        request.reject(
            new Error("Invalid response from C++ backend")
        );
    }
});

cppProcess.stderr.on("data", (data) => {

    console.error(
        "C++ backend:",
        data.toString()
    );
});

cppProcess.on("error", (error) => {

    console.error(
        "Failed to start C++ backend:",
        error.message
    );
});

function sendToCpp(command) {

    return new Promise((resolve, reject) => {

        pendingRequests.push({
            resolve,
            reject
        });

        cppProcess.stdin.write(
            JSON.stringify(command) + "\n"
        );
    });
}

function sendJson(response, statusCode, data) {

    response.writeHead(
        statusCode,
        {
            "Content-Type": "application/json",
            "Access-Control-Allow-Origin": "*"
        }
    );

    response.end(
        JSON.stringify(data)
    );
}

function parseRequestBody(request) {

    return new Promise((resolve, reject) => {

        let body = "";

        request.on("data", (chunk) => {
            body += chunk;
        });

        request.on("end", () => {

            if (!body) {
                resolve({});
                return;
            }

            try {
                resolve(JSON.parse(body));
            }
            catch (error) {
                reject(
                    new Error("Invalid JSON request")
                );
            }
        });
    });
}

const server = http.createServer(
    async (request, response) => {

        if (request.method === "OPTIONS") {

            response.writeHead(
                204,
                {
                    "Access-Control-Allow-Origin": "*",
                    "Access-Control-Allow-Methods":
                        "GET,POST,PUT,DELETE,OPTIONS",
                    "Access-Control-Allow-Headers":
                        "Content-Type"
                }
            );

            response.end();

            return;
        }

        try {

            if (
                request.method === "GET" &&
                request.url === "/api/network"
            ) {

                const result =
                    await sendToCpp({
                        action: "getNetwork"
                    });

                sendJson(
                    response,
                    200,
                    result
                );

                return;
            }

            if (
                request.method === "POST" &&
                request.url === "/api/router"
            ) {

                const body =
                    await parseRequestBody(request);

                const result =
                    await sendToCpp({
                        action: "addRouter",
                        routerId: body.routerId
                    });

                sendJson(
                    response,
                    200,
                    result
                );

                return;
            }

            if (
                request.method === "DELETE" &&
                request.url === "/api/router"
            ) {

                const body =
                    await parseRequestBody(request);

                const result =
                    await sendToCpp({
                        action: "removeRouter",
                        routerId: body.routerId
                    });

                sendJson(
                    response,
                    200,
                    result
                );

                return;
            }

            if (
                request.method === "POST" &&
                request.url === "/api/link"
            ) {

                const body =
                    await parseRequestBody(request);

                const result =
                    await sendToCpp({
                        action: "addLink",
                        routerA: body.routerA,
                        routerB: body.routerB,
                        cost: body.cost,
                        latency: body.latency,
                        bandwidth: body.bandwidth
                    });

                sendJson(
                    response,
                    200,
                    result
                );

                return;
            }

            if (
                request.method === "PUT" &&
                request.url === "/api/link"
            ) {

                const body =
                    await parseRequestBody(request);

                const result =
                    await sendToCpp({
                        action: "updateLink",
                        routerA: body.routerA,
                        routerB: body.routerB,
                        cost: body.cost,
                        latency: body.latency,
                        bandwidth: body.bandwidth
                    });

                sendJson(
                    response,
                    200,
                    result
                );

                return;
            }

            if (
                request.method === "DELETE" &&
                request.url === "/api/link"
            ) {

                const body =
                    await parseRequestBody(request);

                const result =
                    await sendToCpp({
                        action: "removeLink",
                        routerA: body.routerA,
                        routerB: body.routerB
                    });

                sendJson(
                    response,
                    200,
                    result
                );

                return;
            }

            if (
                request.method === "POST" &&
                request.url === "/api/route"
            ) {

                const body =
                    await parseRequestBody(request);

                const result =
                    await sendToCpp({
                        action: "findRoute",
                        source: body.source,
                        destination: body.destination,
                        algorithm: body.algorithm,
                        metric: body.metric || "COST"
                    });

                sendJson(
                    response,
                    200,
                    result
                );

                return;
            }

            if (request.method === "GET") {

    let requestedPath = request.url.split("?")[0];

    if (requestedPath === "/") {
        requestedPath = "/index.html";
    }

    const filePath = path.join(
        frontendDirectory,
        requestedPath
    );

    if (filePath.startsWith(frontendDirectory)) {

        if (fs.existsSync(filePath)) {

            const extension =
                path.extname(filePath);

            const contentTypes = {
                ".html": "text/html",
                ".css": "text/css",
                ".js": "application/javascript",
                ".svg": "image/svg+xml",
                ".png": "image/png",
                ".jpg": "image/jpeg"
            };

            const contentType =
                contentTypes[extension] ||
                "application/octet-stream";

            response.writeHead(
                200,
                {
                    "Content-Type": contentType
                }
            );

            response.end(
                fs.readFileSync(filePath)
            );

            return;
        }
    }
}
            sendJson(
                response,
                404,
                {
                    error: "Endpoint not found"
                }
            );
        }
        catch (error) {

            console.error(error);

            sendJson(
                response,
                500,
                {
                    error: error.message
                }
            );
        }
    }
);

server.listen(
    PORT,
    "0.0.0.0",
    () => {

        console.log(
            `Node.js server running on http://localhost:${PORT}`
        );

        console.log(
            "C++ backend process started."
        );
    }
);

process.on("SIGINT", () => {

    cppProcess.stdin.write(
        JSON.stringify({
            action: "exit"
        }) + "\n"
    );

    cppProcess.kill();

    server.close();

    process.exit(0);
});