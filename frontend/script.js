// ==========================================
// Intelligent Network Route Optimizer
// Phase 6 - Node.js Backend Integration
// ==========================================

let routers = [];

let links = [];

let selectedRoute = [];

const networkCanvas =
    document.getElementById("networkCanvas");

const routingResult =
    document.getElementById("routingResult");


// ==========================================
// Node.js API
// ==========================================

const API_BASE_URL =
    "http://localhost:3000/api";


async function sendApiRequest(
    endpoint,
    options = {}
) {

    const response =
        await fetch(
            `${API_BASE_URL}${endpoint}`,
            {
                ...options,

                headers: {
                    "Content-Type":
                        "application/json",

                    ...(options.headers || {})
                }
            }
        );

    const data =
        await response.json();

    if (
        !response.ok ||
        data.error
    ) {

        throw new Error(
            data.error ||
            "API request failed."
        );
    }

    return data;
}


// ==========================================
// Load Network From Backend
// ==========================================

async function loadNetwork() {

    try {

        const network =
            await sendApiRequest(
                "/network"
            );

        routers =
            network.routers || [];

        links =
            network.links || [];

        selectedRoute = [];

        renderNetwork();

    }
    catch (error) {

        console.error(
            "Failed to load network:",
            error
        );

        alert(
            "Could not connect to the Node.js backend. " +
            "Make sure the server is running."
        );
    }
}


// ==========================================
// Initialize SVG
// ==========================================

function initializeSVG() {

    networkCanvas.innerHTML = "";

    const svg =
        document.createElementNS(
            "http://www.w3.org/2000/svg",
            "svg"
        );

    svg.setAttribute(
        "width",
        "100%"
    );

    svg.setAttribute(
        "height",
        "100%"
    );

    svg.setAttribute(
        "viewBox",
        "0 0 800 500"
    );

    svg.id =
        "networkSVG";

    networkCanvas.appendChild(svg);
}


// ==========================================
// Add Router
// ==========================================

async function addRouter(routerId) {

    if (!routerId) {
        return;
    }

    try {

        await sendApiRequest(
            "/router",
            {
                method: "POST",

                body: JSON.stringify({
                    routerId: routerId
                })
            }
        );

        await loadNetwork();

    }
    catch (error) {

        alert(error.message);
    }
}


// ==========================================
// Delete Router
// ==========================================

async function deleteRouter(routerId) {

    if (!routerId) {
        return;
    }

    try {

        await sendApiRequest(
            "/router",
            {
                method: "DELETE",

                body: JSON.stringify({
                    routerId: routerId
                })
            }
        );

        await loadNetwork();

    }
    catch (error) {

        alert(error.message);
    }
}


// ==========================================
// Add Link
// ==========================================

async function addLink(
    routerA,
    routerB,
    cost,
    latency,
    bandwidth
) {

    if (!routerA || !routerB) {
        return;
    }

    try {

        await sendApiRequest(
            "/link",
            {
                method: "POST",

                body: JSON.stringify({
                    routerA: routerA,
                    routerB: routerB,

                    cost:
                        Number(cost),

                    latency:
                        Number(latency),

                    bandwidth:
                        Number(bandwidth)
                })
            }
        );

        await loadNetwork();

    }
    catch (error) {

        alert(error.message);
    }
}


// ==========================================
// Update Link
// ==========================================

async function updateLink(
    routerA,
    routerB,
    cost,
    latency,
    bandwidth
) {

    if (!routerA || !routerB) {
        return;
    }

    try {

        await sendApiRequest(
            "/link",
            {
                method: "PUT",

                body: JSON.stringify({
                    routerA: routerA,
                    routerB: routerB,

                    cost:
                        Number(cost),

                    latency:
                        Number(latency),

                    bandwidth:
                        Number(bandwidth)
                })
            }
        );

        await loadNetwork();

    }
    catch (error) {

        alert(error.message);
    }
}


// ==========================================
// Delete Link
// ==========================================

async function deleteLink(
    routerA,
    routerB
) {

    if (!routerA || !routerB) {
        return;
    }

    try {

        await sendApiRequest(
            "/link",
            {
                method: "DELETE",

                body: JSON.stringify({
                    routerA: routerA,
                    routerB: routerB
                })
            }
        );

        await loadNetwork();

    }
    catch (error) {

        alert(error.message);
    }
}


// ==========================================
// Router Position
// ==========================================

function getRouterPosition(
    routerId,
    index
) {

    const total =
        routers.length;

    const centerX = 400;

    const centerY = 250;

    const radius = 180;


    if (total === 1) {

        return {
            x: centerX,
            y: centerY
        };
    }


    const angle =
        (2 * Math.PI * index) /
        total;


    return {

        x:
            centerX +
            radius *
            Math.cos(angle),

        y:
            centerY +
            radius *
            Math.sin(angle)
    };
}


// ==========================================
// Check Selected Route
// ==========================================

function isLinkInRoute(
    routerA,
    routerB
) {

    for (
        let i = 0;
        i < selectedRoute.length - 1;
        i++
    ) {

        const first =
            selectedRoute[i];

        const second =
            selectedRoute[i + 1];


        if (
            (
                first === routerA &&
                second === routerB
            )
            ||
            (
                first === routerB &&
                second === routerA
            )
        ) {

            return true;
        }
    }

    return false;
}


// ==========================================
// Render Network
// ==========================================

function renderNetwork() {

    const svg =
        document.getElementById(
            "networkSVG"
        );


    if (!svg) {

        initializeSVG();

        return;
    }


    svg.innerHTML = "";


    const positions = {};


// --------------------------------------
// Calculate router positions
// --------------------------------------

    routers.forEach(
        (router, index) => {

            positions[router] =
                getRouterPosition(
                    router,
                    index
                );
        }
    );


// --------------------------------------
// Draw links
// --------------------------------------

    links.forEach(
        link => {

            const start =
                positions[
                    link.routerA
                ];

            const end =
                positions[
                    link.routerB
                ];


            if (!start || !end) {
                return;
            }


            const highlighted =
                isLinkInRoute(
                    link.routerA,
                    link.routerB
                );


// --------------------------------
// Line
// --------------------------------

            const line =
                document.createElementNS(
                    "http://www.w3.org/2000/svg",
                    "line"
                );


            line.setAttribute(
                "x1",
                start.x
            );

            line.setAttribute(
                "y1",
                start.y
            );

            line.setAttribute(
                "x2",
                end.x
            );

            line.setAttribute(
                "y2",
                end.y
            );


            line.setAttribute(
                "stroke",
                highlighted
                    ? "#2563eb"
                    : "#94a3b8"
            );


            line.setAttribute(
                "stroke-width",
                highlighted
                    ? "6"
                    : "3"
            );


            svg.appendChild(line);


// --------------------------------
// Link metrics
// --------------------------------

            const text =
                document.createElementNS(
                    "http://www.w3.org/2000/svg",
                    "text"
                );


            text.setAttribute(
                "x",
                (start.x + end.x) / 2
            );


            text.setAttribute(
                "y",
                (start.y + end.y) / 2 - 10
            );


            text.setAttribute(
                "text-anchor",
                "middle"
            );


            text.setAttribute(
                "font-size",
                "13"
            );


            text.textContent =
                `C:${link.cost}  ` +
                `L:${link.latency}  ` +
                `B:${link.bandwidth}`;


            svg.appendChild(text);
        }
    );


// --------------------------------------
// Draw routers
// --------------------------------------

    routers.forEach(
        router => {

            const position =
                positions[router];


// --------------------------------
// Circle
// --------------------------------

            const circle =
                document.createElementNS(
                    "http://www.w3.org/2000/svg",
                    "circle"
                );


            circle.setAttribute(
                "cx",
                position.x
            );


            circle.setAttribute(
                "cy",
                position.y
            );


            circle.setAttribute(
                "r",
                "30"
            );


            circle.setAttribute(
                "fill",
                "#ffffff"
            );


            circle.setAttribute(
                "stroke",
                "#2563eb"
            );


            circle.setAttribute(
                "stroke-width",
                "4"
            );


            svg.appendChild(circle);


// --------------------------------
// Router ID
// --------------------------------

            const text =
                document.createElementNS(
                    "http://www.w3.org/2000/svg",
                    "text"
                );


            text.setAttribute(
                "x",
                position.x
            );


            text.setAttribute(
                "y",
                position.y + 5
            );


            text.setAttribute(
                "text-anchor",
                "middle"
            );


            text.setAttribute(
                "font-size",
                "16"
            );


            text.setAttribute(
                "font-weight",
                "bold"
            );


            text.textContent =
                router;


            svg.appendChild(text);
        }
    );
}


// ==========================================
// Display Routing Result
// ==========================================

function displayRoutingResult(
    algorithm,
    metric,
    route,
    cost
) {

    if (
        !route ||
        route.length === 0
    ) {

        routingResult.innerHTML =
            "<p>No route found.</p>";

        selectedRoute = [];

        renderNetwork();

        return;
    }


    selectedRoute =
        route;


    routingResult.innerHTML = `

        <div class="result-item">
            <strong>Algorithm:</strong>
            ${algorithm}
        </div>

        <div class="result-item">
            <strong>Routing Metric:</strong>
            ${metric}
        </div>

        <div class="result-item">
            <strong>Route:</strong>
            ${route.join(" → ")}
        </div>

        <div class="result-item">
            <strong>Cost:</strong>
            ${cost}
        </div>

    `;


    renderNetwork();
}


// ==========================================
// Start
// ==========================================

initializeSVG();

loadNetwork();


// ==========================================
// UI Event Handlers
// ==========================================


// ==========================================
// Add Router
// ==========================================

document
    .getElementById("addRouterBtn")
    .addEventListener(
        "click",
        async function () {

            const routerId =
                document
                    .getElementById(
                        "routerId"
                    )
                    .value
                    .trim();


            await addRouter(
                routerId
            );


            document
                .getElementById(
                    "routerId"
                )
                .value = "";
        }
    );


// ==========================================
// Delete Router
// ==========================================

document
    .getElementById("deleteRouterBtn")
    .addEventListener(
        "click",
        async function () {

            const routerId =
                document
                    .getElementById(
                        "deleteRouterId"
                    )
                    .value
                    .trim();


            await deleteRouter(
                routerId
            );


            document
                .getElementById(
                    "deleteRouterId"
                )
                .value = "";
        }
    );


// ==========================================
// Add Link
// ==========================================

document
    .getElementById("addLinkBtn")
    .addEventListener(
        "click",
        async function () {

            const routerA =
                document
                    .getElementById(
                        "routerA"
                    )
                    .value
                    .trim();


            const routerB =
                document
                    .getElementById(
                        "routerB"
                    )
                    .value
                    .trim();


            const cost =
                document
                    .getElementById(
                        "cost"
                    )
                    .value;


            const latency =
                document
                    .getElementById(
                        "latency"
                    )
                    .value;


            const bandwidth =
                document
                    .getElementById(
                        "bandwidth"
                    )
                    .value;


            await addLink(
                routerA,
                routerB,
                cost,
                latency,
                bandwidth
            );
        }
    );


// ==========================================
// Update Link
// ==========================================

document
    .getElementById("updateLinkBtn")
    .addEventListener(
        "click",
        async function () {

            const routerA =
                document
                    .getElementById(
                        "routerA"
                    )
                    .value
                    .trim();


            const routerB =
                document
                    .getElementById(
                        "routerB"
                    )
                    .value
                    .trim();


            const cost =
                document
                    .getElementById(
                        "cost"
                    )
                    .value;


            const latency =
                document
                    .getElementById(
                        "latency"
                    )
                    .value;


            const bandwidth =
                document
                    .getElementById(
                        "bandwidth"
                    )
                    .value;


            await updateLink(
                routerA,
                routerB,
                cost,
                latency,
                bandwidth
            );
        }
    );


// ==========================================
// Delete Link
// ==========================================

document
    .getElementById("deleteLinkBtn")
    .addEventListener(
        "click",
        async function () {

            const routerA =
                document
                    .getElementById(
                        "routerA"
                    )
                    .value
                    .trim();


            const routerB =
                document
                    .getElementById(
                        "routerB"
                    )
                    .value
                    .trim();


            await deleteLink(
                routerA,
                routerB
            );
        }
    );


// ==========================================
// Find Route
// ==========================================

document
    .getElementById("findRouteBtn")
    .addEventListener(
        "click",
        async function () {

            const source =
                document
                    .getElementById(
                        "source"
                    )
                    .value
                    .trim();


            const destination =
                document
                    .getElementById(
                        "destination"
                    )
                    .value
                    .trim();


            const algorithm =
                document
                    .getElementById(
                        "algorithm"
                    )
                    .value;


            const metric =
                document
                    .getElementById(
                        "metric"
                    )
                    .value;


            if (
                source === "" ||
                destination === ""
            ) {

                alert(
                    "Please enter source and destination routers."
                );

                return;
            }


            if (
                !routers.includes(
                    source
                )
            ) {

                alert(
                    "Source router does not exist."
                );

                return;
            }


            if (
                !routers.includes(
                    destination
                )
            ) {

                alert(
                    "Destination router does not exist."
                );

                return;
            }


            try {

                const result =
                    await sendApiRequest(
                        "/route",
                        {
                            method: "POST",

                            body:
                                JSON.stringify({
                                    source:
                                        source,

                                    destination:
                                        destination,

                                    algorithm:
                                        algorithm,

                                    metric:
                                        metric
                                })
                        }
                    );


                if (
                    !result.found
                ) {

                    displayRoutingResult(
                        algorithm,
                        metric,
                        [],
                        -1
                    );

                    return;
                }


                displayRoutingResult(
                    algorithm,
                    metric,
                    result.path,
                    result.cost
                );

            }
            catch (error) {

                alert(
                    error.message
                );
            }
        }
    );