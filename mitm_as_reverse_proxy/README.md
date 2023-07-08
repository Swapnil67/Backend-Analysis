# MITM as Reverse Proxy
# Using this we can intercept traffice b/w two services

$ mitmweb --mode reverse:http://localhost:6002 -p 6001

Here mitm will act as a reverse proxy 

Client talk to Service A (6793)
Service A talks to MITM Reverse Proxy (6001)
MITM Talks to Service B (6002)

So we can say that Client does not have knowledge of which backend its request are going to 
And we are intercepting the Traffic Between two services successfully