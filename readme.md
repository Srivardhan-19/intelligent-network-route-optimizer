# Intelligent Network Route Optimizer

A DSA-based computer network routing simulator that finds and visualizes the best route for packets based on different network parameters.

## Project Goal

The project models a computer network as a weighted graph and uses DSA-based routing algorithms to find optimal routes between routers.

The project combines:

* Data Structures and Algorithms
* Computer Networks
* Lightweight frontend visualization

## Planned Features

* Graph-based network topology
* BFS routing
* Dijkstra routing
* Bellman-Ford routing
* Multiple network routing strategies
* Bandwidth-aware routing
* Delay-aware routing
* Packet-loss-aware routing
* Congestion-aware routing
* Balanced routing
* Routing table simulation
* Packet forwarding simulation
* Link and router failure simulation
* Route recovery
* Network visualization

---

# Project Status

## Phase 1 — Graph Foundation ✅

The basic network graph structure was implemented.

### Completed

* Router representation
* Graph adjacency-list representation
* Adding routers
* Adding links
* Removing links
* Checking whether a link exists
* Retrieving neighboring routers
* Graph display
* Graph test cases

The network is represented using an adjacency list, allowing routers and their connections to be stored and accessed efficiently.

---

## Phase 2 — Routing Algorithms ✅

Three routing algorithms were implemented and tested.

### BFS

Breadth-First Search is used for **minimum-hop routing**.

BFS finds a route with the smallest number of links between the source and destination routers.

Tested cases:

* Shortest-hop route
* Same source and destination
* Unreachable destination
* Disconnected routers

All BFS tests passed.

### Dijkstra

Dijkstra's algorithm is used for **minimum-cost routing**.

It considers link weights and can select a route with more hops when that route has a lower total cost.

Tested cases:

* Lowest-cost route
* Same source and destination
* Unreachable destination
* Cheapest route with more hops

All Dijkstra tests passed.

### Bellman-Ford

Bellman-Ford is used for **minimum-cost routing with negative-cycle detection**.

Tested cases:

* Lowest-cost route
* Same source and destination
* Unreachable destination
* Cheapest route with more hops
* Negative-cycle detection

All Bellman-Ford tests passed.

### Algorithm Comparison

The routing algorithms were compared using the same network.

Example:

```text
BFS route:
R1 → R2 → R4
Hops: 2

Dijkstra route:
R1 → R3 → R4
Cost: 4

Bellman-Ford route:
R1 → R3 → R4
Cost: 4
```

This demonstrates that different algorithms can optimize different objectives.

### Phase 2 Conclusion

```text
BFS
→ Minimum number of hops

Dijkstra
→ Minimum network cost

Bellman-Ford
→ Minimum network cost + negative-cycle detection
```

---

# Phase 3 — Network Metrics & Multi-Metric Routing ✅

Phase 3 extended the graph model to support multiple network metrics.

## Link Metrics

Network links can now contain:

* Cost
* Latency
* Bandwidth

The graph was updated to store and retrieve these metrics while preserving the reverse-link information.

### Link Metric Tests

The following were tested:

* Neighbor stored correctly
* Cost stored correctly
* Latency stored correctly
* Bandwidth stored correctly
* Reverse link preserves all metrics

All link metric tests passed.

---

## Metric-Based Routing

The routing system can optimize different network characteristics.

### Cost Optimization

Selects the route with the lowest total cost.

### Latency Optimization

Selects the route with the lowest total latency.

### Bandwidth Optimization

Selects the route with the highest available bandwidth.

Tests confirmed that different metrics can select different routes through the same network.

---

## Metric Normalization

Cost, latency, and bandwidth can have different scales, so metric normalization was introduced before combining them into a single routing score.

```text
Cost
   ↓
Normalization
   ↓
Normalized cost

Latency
   ↓
Normalization
   ↓
Normalized latency

Bandwidth
   ↓
Normalization
   ↓
Normalized bandwidth
```

All metric normalization tests passed.

---

## Route Scoring

A route scoring system was introduced to calculate a combined score from normalized network metrics.

The general process is:

```text
Network metrics
      ↓
Normalization
      ↓
Routing weights
      ↓
Combined route score
      ↓
Route preference
```

The route score calculation was tested successfully.

---

## Weighted Routing

Routing weights allow different network objectives to have different importance.

For example, the routing system can prioritize:

* Lower cost
* Better performance
* Higher bandwidth
* A combination of these objectives

Tests confirmed that changing the weights can change the preferred route.

All weighted routing tests passed.

---

## Balanced Routing

Balanced routing combines multiple network metrics to select a route according to the configured routing priorities.

Tested cases:

* Balanced routing favors cost
* Balanced routing favors performance
* Changing weights changes the selected route
* Same source and destination
* Unreachable destination

All balanced routing tests passed.

---

# Phase 3 Regression Testing

The Phase 3 implementation was also tested against the existing Phase 2 routing algorithms.

### BFS

```text
All BFS tests passed
```

### Dijkstra

```text
All Dijkstra tests passed
```

### Bellman-Ford

```text
All Bellman-Ford tests passed
```

This confirmed that the addition of multiple network metrics did not break the existing routing algorithms.

---

# Phase 4 — Dynamic Network Topology ✅

Phase 4 extended the network graph to support dynamic changes to routers, links, and link metrics.

The routing algorithms can now operate on the updated network topology without requiring the graph to be recreated.

---

## Dynamic Router Management

The graph now supports dynamic router management.

### Completed

* Adding routers
* Deleting routers
* Duplicate router handling
* Nonexistent router handling
* Removing connected links when a router is deleted

When a router is deleted, all links connected to that router are also removed from the graph.

---

## Dynamic Link Management

The graph now supports dynamic link management.

### Completed

* Adding links
* Removing links
* Updating link information
* Updating cost
* Updating latency
* Updating bandwidth
* Maintaining reverse-link consistency
* Nonexistent link handling

Since the network is undirected, changes to a link are reflected in both directions.

For example:

```text
R1 ───────── R2

Update:
Cost
Latency
Bandwidth

↓

R1 ───────── R2
Updated metrics stored in both directions
```

---

## Dynamic Graph Testing

Dynamic graph operations were tested through complete topology modification sequences.

```text
Create routers
      ↓
Create links
      ↓
Update link metrics
      ↓
Delete link
      ↓
Delete router
      ↓
Verify remaining topology
```

The tests verified that the graph remains consistent after multiple topology changes.

All dynamic graph tests passed.

---

## Routing After Topology Changes

The existing routing algorithms were tested after changes were made to the network topology.

The routing system recalculates routes using the current state of the graph.

### Tested Routing Algorithms

* BFS
* Dijkstra
* Bellman-Ford

### Tested Multi-Metric Routing

* Cost routing
* Latency routing
* Bandwidth routing

### Tested Advanced Routing

* Weighted routing
* Balanced routing

The tests confirmed that routing adapts correctly after:

* Adding links
* Removing links
* Updating link metrics
* Deleting routers
* Making destinations unreachable

All routing topology-change tests passed.

---

## Phase 4 Integration Testing

A complete integration test was created to verify the interaction between dynamic topology management and routing.

The integration flow is:

```text
Create routers
      ↓
Create links
      ↓
Run routing
      ↓
Update link metrics
      ↓
Run routing again
      ↓
Delete links
      ↓
Run routing again
      ↓
Delete router
      ↓
Verify final topology
```

### Integration Test Results

```text
Test 1 passed: routers created
Test 2 passed: links created with network metrics
Test 3 passed: initial cost route is R1 -> R2 -> R4
Test 4 passed: route changed after metric update
Test 5 passed: reverse link metrics updated correctly
Test 6 passed: routing uses remaining route after link deletion
Test 7 passed: routing detects unreachable destination
Test 8 passed: router deletion removes connected topology
Test 9 passed: final graph topology is consistent

All Phase 4 integration tests passed!
```

---

# Phase 5 — Frontend & Final Integration ✅

Phase 5 added the frontend interface and backend API layer for interacting with the network routing system.

## Frontend

The frontend is implemented using:

* HTML
* CSS
* JavaScript
* SVG

The interface is organized into:

* Network Controls
* Routing
* Visualization
* Routing Result

### Network Controls

The frontend supports:

* Adding routers
* Deleting routers
* Adding links
* Updating link metrics
* Deleting links
* Input validation

### Network Visualization

The network topology is visualized using SVG.

The visualization displays:

* Routers
* Network links
* Link cost
* Link latency
* Link bandwidth
* Selected route highlighting

The visualization updates when the network topology changes.

### Routing Interface

The frontend provides controls for:

* Source router
* Destination router
* Routing algorithm
* Routing metric
* Find Route operation

The available routing algorithms are:

* BFS
* Dijkstra
* Bellman-Ford

The actual routing algorithms remain implemented in the C++ backend. Frontend-to-backend routing integration will be completed in Phase 6 using Node.js.

---

## Network API

A `NetworkAPI` interface was added to provide a higher-level interface between the frontend-facing API layer and the C++ network graph.

The API supports:

* Adding routers
* Removing routers
* Adding links
* Updating links
* Removing links
* Finding routes
* Retrieving network information as JSON

---

## Network JSON

The network topology can be exported as JSON containing:

* Routers
* Links
* Cost
* Latency
* Bandwidth

The JSON output was tested after:

* Adding routers
* Updating link metrics
* Removing links

All Network JSON tests passed.

---

## Router API Testing

The Router API was tested for:

* Adding routers
* Duplicate router handling
* Creating router connections
* Deleting routers
* Removing connected links
* Nonexistent router handling
* Final topology consistency

Test results:

```text
Test 1 passed: routers added through API
Test 2 passed: duplicate router handled
Test 3 passed: router connections created
Test 4 passed: router deleted with connected links
Test 5 passed: remaining topology is consistent
Test 6 passed: nonexistent router handled

All Router API tests passed!
# Phase 6 — Node.js Backend Integration

Phase 6 connected the HTML/CSS/JavaScript frontend with the existing C++ routing backend through a Node.js API server.

## Architecture

```text
Frontend
    ↓ HTTP / JSON
Node.js API Server
    ↓ stdin / stdout JSON
C++ API Bridge
    ↓
NetworkAPI
    ↓
Graph + Routing Algorithms
```

## Node.js Backend

Implemented a Node.js HTTP API server using Node.js built-in modules.

The API provides:

* Get network topology
* Add router
* Delete router
* Add link
* Update link
* Delete link
* Find route

The Node.js server communicates with the existing C++ routing system without moving the routing algorithms into JavaScript.

## C++ API Bridge

Implemented a C++ API bridge to connect the Node.js server with the existing C++ backend.

The bridge communicates using JSON messages through standard input and output.

This allows the Node.js server to send network and routing requests to the C++ `NetworkAPI` while keeping the existing graph and routing architecture unchanged.

## Frontend Integration

The frontend was connected to the Node.js API.

The frontend now performs network operations through the backend instead of handling the network state only in JavaScript.

Implemented:

* Router creation through API
* Router deletion through API
* Link creation through API
* Link metric updates through API
* Link deletion through API
* Network topology loading from backend
* Route calculation through backend
* Route result display
* Route visualization and highlighting

## API Operations

The following backend operations were integrated with the frontend:

```text
GET    /api/network
POST   /api/router
DELETE /api/router
POST   /api/link
PUT    /api/link
DELETE /api/link
POST   /api/route
```

## Routing Integration

The frontend can request routes from the C++ routing algorithms through the Node.js backend.

Supported algorithms:

* BFS
* Dijkstra
* Bellman-Ford

Supported routing metrics:

* Cost
* Latency
* Bandwidth

The calculated route is returned from the C++ backend and displayed in the frontend.

The selected route is also highlighted in the network visualization.

## CORS Configuration

Cross-origin communication was configured so that the frontend running through Live Server can communicate with the Node.js API server.

The API supports the required HTTP methods:

```text
GET
POST
PUT
DELETE
OPTIONS
```

## Phase 6 Integration Testing

The complete frontend → Node.js → C++ integration was tested successfully.

Verified:

```text
Router creation                    Passed
Link creation                     Passed
Link update                       Passed
Link deletion                     Passed
Router deletion                   Passed
Network visualization             Passed
BFS routing                       Passed
Dijkstra routing                  Passed
Bellman-Ford routing              Passed
Cost metric routing               Passed
Latency metric routing            Passed
Bandwidth metric routing          Passed
Unreachable route detection       Passed
Route visualization               Passed
```

### Final Integration Test

A complete topology update and routing workflow was also tested:

```text
1. Created routers R1, R2, R3 and R4
2. Created multiple network links
3. Calculated an initial route
4. Updated link metrics
5. Verified that routing changed accordingly
6. Deleted a link
7. Verified the remaining route
8. Deleted router R3
9. Verified that its connected links were removed
10. Verified that the remaining network topology was consistent
```

All Phase 6 integration tests passed.

## Phase 6 Status

```text
Phase 6 — Node.js Backend Integration
Complete ✅
```

---

## Current Project Status

Phase 1 — Graph Foundation
Complete ✅

Phase 2 — Routing Algorithms
Complete ✅

Phase 3 — Network Metrics & Multi-Metric Routing
Complete ✅

Phase 4 — Dynamic Network Topology
Complete ✅

Phase 5 — Frontend & Final Integration
Complete ✅

Phase 6 — Node.js Backend Integration
Complete ✅

Phase 7 — Deployment & Final Validation
Not started ⏳
