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

# Current Architecture

The routing system developed so far can be summarized as:

```text
                    Network Graph
                         │
                         ▼
                  Dynamic Topology
                         │
              ┌──────────┼──────────┐
              ▼          ▼          ▼
           Routers      Links    Link Metrics
                                    │
                         ┌──────────┼──────────┐
                         ▼          ▼          ▼
                       Cost      Latency    Bandwidth
                         │          │          │
                         └──────────┼──────────┘
                                    ▼
                            Metric Normalization
                                    │
                                    ▼
                              Route Scoring
                                    │
                                    ▼
                           Routing Algorithms
                         ┌──────────┼──────────┐
                         ▼          ▼          ▼
                        BFS      Dijkstra   Bellman-Ford
                                    │
                                    ▼
                             Weighted Routing
                                    │
                                    ▼
                             Balanced Routing
                                    │
                                    ▼
                              Selected Route
```

# Current Project Status

```text
Phase 1 — Graph Foundation

Complete ✅

Phase 2 — Routing Algorithms

Complete ✅

Phase 3 — Network Metrics & Multi-Metric Routing

Complete ✅

Phase 4 — Dynamic Network Topology

Complete ✅
```

**Current status: Phase 4 complete.**
