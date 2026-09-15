// ==========================================
// Intelligent Network Route Optimizer
// Phase 5.2 - SVG Network Visualization
// ==========================================

let routers = [];

let links = [];

let selectedRoute = [];

const networkCanvas =
    document.getElementById("networkCanvas");

const routingResult =
    document.getElementById("routingResult");


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

    svg.setAttribute("width", "100%");
    svg.setAttribute("height", "100%");
    svg.setAttribute("viewBox", "0 0 800 500");

    svg.id = "networkSVG";

    networkCanvas.appendChild(svg);
}


// ==========================================
// Add Router
// ==========================================

function addRouter(routerId) {

    if (!routerId) {
        return;
    }

    if (routers.includes(routerId)) {
        alert("Router already exists.");
        return;
    }

    routers.push(routerId);

    renderNetwork();
}


// ==========================================
// Delete Router
// ==========================================

function deleteRouter(routerId) {

    if (!routerId) {
        return;
    }

    if (!routers.includes(routerId)) {
        alert("Router does not exist.");
        return;
    }

    routers = routers.filter(
        router => router !== routerId
    );

    // Remove links connected to router
    links = links.filter(
        link =>
            link.routerA !== routerId &&
            link.routerB !== routerId
    );

    selectedRoute = [];

    renderNetwork();
}


// ==========================================
// Add Link
// ==========================================

function addLink(
    routerA,
    routerB,
    cost,
    latency,
    bandwidth
) {

    if (!routerA || !routerB) {
        return;
    }

    if (routerA === routerB) {
        alert("A router cannot connect to itself.");
        return;
    }

    if (
        !routers.includes(routerA) ||
        !routers.includes(routerB)
    ) {
        alert("Both routers must exist.");
        return;
    }

    const exists = links.some(
        link =>
            (
                link.routerA === routerA &&
                link.routerB === routerB
            ) ||
            (
                link.routerA === routerB &&
                link.routerB === routerA
            )
    );

    if (exists) {
        alert("Link already exists.");
        return;
    }

    links.push({
        routerA: routerA,
        routerB: routerB,
        cost: Number(cost),
        latency: Number(latency),
        bandwidth: Number(bandwidth)
    });

    renderNetwork();
}


// ==========================================
// Update Link
// ==========================================

function updateLink(
    routerA,
    routerB,
    cost,
    latency,
    bandwidth
) {

    const link = links.find(
        link =>
            (
                link.routerA === routerA &&
                link.routerB === routerB
            ) ||
            (
                link.routerA === routerB &&
                link.routerB === routerA
            )
    );

    if (!link) {
        alert("Link does not exist.");
        return;
    }

    link.cost = Number(cost);
    link.latency = Number(latency);
    link.bandwidth = Number(bandwidth);

    renderNetwork();
}


// ==========================================
// Delete Link
// ==========================================

function deleteLink(
    routerA,
    routerB
) {

    const oldLength = links.length;

    links = links.filter(
        link =>
            !(
                (
                    link.routerA === routerA &&
                    link.routerB === routerB
                ) ||
                (
                    link.routerA === routerB &&
                    link.routerB === routerA
                )
            )
    );

    if (links.length === oldLength) {
        alert("Link does not exist.");
        return;
    }

    selectedRoute = [];

    renderNetwork();
}


// ==========================================
// Router Position
// ==========================================

function getRouterPosition(
    routerId,
    index
) {

    const total = routers.length;

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
        (2 * Math.PI * index) / total;

    return {

        x:
            centerX +
            radius * Math.cos(angle),

        y:
            centerY +
            radius * Math.sin(angle)
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
            ) ||
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
        document.getElementById("networkSVG");

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
                positions[link.routerA];

            const end =
                positions[link.routerB];

            if (!start || !end) {
                return;
            }

            const highlighted =
                isLinkInRoute(
                    link.routerA,
                    link.routerB
                );


            // Line
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


            // Circle
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


            // Router ID
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

            text.textContent = router;

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

    if (!route || route.length === 0) {

        routingResult.innerHTML =
            "<p>No route found.</p>";

        selectedRoute = [];

        renderNetwork();

        return;
    }

    selectedRoute = route;

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


// ==========================================
// UI Event Handlers
// ==========================================

// Add Router
document
    .getElementById("addRouterBtn")
    .addEventListener("click", function () {

        const routerId =
            document
                .getElementById("routerId")
                .value
                .trim();

        addRouter(routerId);

        document
            .getElementById("routerId")
            .value = "";
    });


// Delete Router
document
    .getElementById("deleteRouterBtn")
    .addEventListener("click", function () {

        const routerId =
            document
                .getElementById("deleteRouterId")
                .value
                .trim();

        deleteRouter(routerId);

        document
            .getElementById("deleteRouterId")
            .value = "";
    });


// Add Link
document
    .getElementById("addLinkBtn")
    .addEventListener("click", function () {

        const routerA =
            document
                .getElementById("routerA")
                .value
                .trim();

        const routerB =
            document
                .getElementById("routerB")
                .value
                .trim();

        const cost =
            document
                .getElementById("cost")
                .value;

        const latency =
            document
                .getElementById("latency")
                .value;

        const bandwidth =
            document
                .getElementById("bandwidth")
                .value;

        addLink(
            routerA,
            routerB,
            cost,
            latency,
            bandwidth
        );
    });


// Update Link
document
    .getElementById("updateLinkBtn")
    .addEventListener("click", function () {

        const routerA =
            document
                .getElementById("routerA")
                .value
                .trim();

        const routerB =
            document
                .getElementById("routerB")
                .value
                .trim();

        const cost =
            document
                .getElementById("cost")
                .value;

        const latency =
            document
                .getElementById("latency")
                .value;

        const bandwidth =
            document
                .getElementById("bandwidth")
                .value;

        updateLink(
            routerA,
            routerB,
            cost,
            latency,
            bandwidth
        );
    });


// Delete Link
document
    .getElementById("deleteLinkBtn")
    .addEventListener("click", function () {

        const routerA =
            document
                .getElementById("routerA")
                .value
                .trim();

        const routerB =
            document
                .getElementById("routerB")
                .value
                .trim();

        deleteLink(
            routerA,
            routerB
        );
    });

document
    .getElementById("findRouteBtn")
    .addEventListener("click", function () {

        const source =
            document
                .getElementById("source")
                .value
                .trim();

        const destination =
            document
                .getElementById("destination")
                .value
                .trim();

        const algorithm =
            document
                .getElementById("algorithm")
                .value;

        const metric =
            document
                .getElementById("metric")
                .value;

        if (source === "" || destination === "") {
            alert("Please enter source and destination routers.");
            return;
        }

        if (!routers.includes(source)) {
            alert("Source router does not exist.");
            return;
        }

        if (!routers.includes(destination)) {
            alert("Destination router does not exist.");
            return;
        }

        if (source === destination) {
            displayRoutingResult(
                algorithm,
                metric,
                [source],
                0
            );
            return;
        }

        /*
         * Temporary Phase 5 frontend test.
         *
         * Actual BFS / Dijkstra / Bellman-Ford
         * execution will come from the C++ backend
         * through Node.js in Phase 6.
         */
        displayRoutingResult(
            algorithm,
            metric,
            [source, destination],
            0
        );
    });