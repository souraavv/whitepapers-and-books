- [Learn API Design](#learn-api-design)
  - [Types of API](#types-of-api)
  - [RESTful API Design and Best Practices](#restful-api-design-and-best-practices)
  - [RESTful API documentation tools](#restful-api-documentation-tools)
    - [Swagger](#swagger)



# [Learn API Design](https://github.com/dwyl/learn-api-design)
<details>
<summary> Short summary </summary>

> Always make your REST API as small/short as possible. Hard to misuse; Easy to evolve; Sufficiently powerful to satisfy requirements;

## Types of API 
- Remote Procedure Calls (RPC) 
  - Simplest form of API was RPC 
  - Support with JSON and XML 
  - Google created `gRPC` 
- Simple Object Access Protocol (SOAP)
  - RPC had a problem - it didn't distinguish between data types. 
  - So devs had to add additional metadata to label a field with a data type
  - Mostly used by financial services (WS-Security extension) allows encrypt messages
- REpresentation State Transfer (REST)
  - Describes how a system can expose a consistent interface 
  - When you say REST API, it means API is accessed via **HTTP** protocol at a predefined set of URLs
  - While SOAP allows *stateful* interaction - where serve is aware of prev request - RESTful APIs are stateless, thus treating every request as same
    - EXTRA: The reason for stateless RESTful API 
      - Pros
        - **Horizontal scaling** becomes easier with stateless since each request is independent
        - No state maintenance required by the server, allowing request to be distributed across multiple servers wihtout session affinity
        - Stateless servers are more **fault-tolerant** 
        - **Decoupling** client and server are lossely coupled
        - **Caching** Statelessness enables HTTP caching because response can be stored and reused without concern about session-based dependencies
      - Cons 
        - Increased Overhead: Each request contians all necessary info (such as auth token, request context, etc.)
        - Complexity in Client: May need to manage the state (e.g. session )
      -  Why REST was designed Stateless ?
         -  Scalable, loose couple
   -  HTTP Methods
      -  GET, PUT(Idempotent), POST(non-Idempotent), DELETE, PATCH
- Real Time APIs: WebSocket
  - A WebSocket is a real time protocol that enables *bidirectional communication* between web client and web server 
  - Similar to HTTP; WebSocket also works on top of TCP 
  - However, unlike HTTP they are stateful, thus make them suitable for event-driven services that require high-frequency communication
  - Sockets allows client to subscribe to the stream of data, which means that update can be receive after the initial response (Real-Time Apps!)
  - To create a WebSockets connection, an initial HTTP handshake is made, and then establishes a persistent connection where both parties exchange data  

## RESTful API Design and Best Practices
- Provide good resource names
  - Use identifier in the URL instead of query parameters
  - Use plurals in URL segments `/users/123/orders/2/items/1`
  - User lowercase in URL segment and use `-` or `_` as separator
- Use adequate HTTP response code 
- Use query parameters to filter, sort and search resources
  - Sorting, searching and limiting the fields in the JSON response
- Show meaningfull erros 
- Favor JSON over XML 
- Always use SSL 
  - SSL certificates create an encrypted connection and establish trust 
- Rate limiting 


## RESTful API documentation tools
### Swagger
- Open source API documentation framework help developers to design, document and consume RESTful web services
- Swagger reads an API and extract in the form of interactive UI called "Swagger UI" (generate interactive documentation from API)
- Swagger UI offers HTML view of API with JSON support

</details>
