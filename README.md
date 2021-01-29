# Restaurant food order serving.

In this project, we are planning to build a food order-delivery system that would be employed in a restaurant. A meal prepared in the kitchen consists of multiple dishes. A dish can either be an entree or main course. A meal is the plating of all the dishes along with the garnish. Here, it is assumed there are multiple cooks who prepare a specific dish. The dish is finally arranged and garnished by the chef. The delivery of the prepared meal is then served to the specific table by the multiple waiters. We would be using multi-threading for the preparation of the various components that make a dish. Similarly we will use multi-threading for the waiters. For now, we will assume any of the waiter can serve any of the table as long as the dish is ready to be served.

This concept can be easily extended out to multi-processes with shared memory for faster processing. For now, this is out of the scope of this project.

## References
1. https://wang-yimu.com/a-tutorial-on-shared-memory-inter-process-communication/
1. https://www.softprayog.in/programming/interprocess-communication-using-system-v-shared-memory-in-linux
1. https://www.geeksforgeeks.org/ipc-shared-memory/
