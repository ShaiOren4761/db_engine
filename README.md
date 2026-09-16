An educational database engine written in C to explore binary storage,
schema representation, row serialization, query parsing, and network
service design.

> Status: Active development. In-memory row storage and basic binary
> persistence are implemented. JSON command parsing is currently in
> progress; an HTTP interface is planned next.

## Current capabilities

- Define tables with fixed-width typed fields
- Manage multiple table schemas through a database context
- Write packed rows into an in-memory buffer
- Retrieve individual rows or copy row ranges
- Persist table data to a binary file

## In progress

- Parse JSON commands
- Validate parsed values against table schemas

## Planned

- Query/command execution layer
- HTTP server and request routing
- Automated tests
- Improved error handling and resource ownership
