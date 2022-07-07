// #######################
// Soodeh Vanaki
// Fall 2020 - BTS530
// Housing Api
// #######################
// ################################################################################
// Web service setup

const express = require("express");
const cors = require("cors");
const path = require("path");
const bodyParser = require('body-parser');
const app = express();
const HTTP_PORT = process.env.PORT || 8080;
// Or use some other port number that you like better

// Add support for incoming JSON entities
app.use(bodyParser.json());
// Add support for CORS
app.use(cors());



// ################################################################################
// Data model and persistent store setup

const manager = require("./manager.js");
const m = manager();



// ################################################################################
// Deliver the app's home page to browser clients

app.get("/", (req, res) => {
  res.sendFile(path.join(__dirname, "/index.html"));
});



// ################################################################################
// Resources available in this web API

app.get("/api", (req, res) => {
  // Here are the resources that are available for users of this web API...
  const links = [];
  // This app's resources...
  links.push({ "rel": "collection", "href": "/api/user", "methods": "GET,POST" });
  links.push({ "rel": "collection", "href": "/api/user/name/:text", "methods": "", "title": "Search" });
  links.push({ "rel": "collection", "href": "/api/user/:id", "methods": "DELETE" });
  //links.push({ "rel": "collection", "href": "/api/user/:id/property", "methods": "GET", "title": "Properties for specific User" });
  links.push({ "rel": "item", "href": "/api/user/:id", "methods": "GET" });
  //links.push({ "rel": "item", "href": "/api/user/:id/with-property", "methods": "GET" });
  links.push({ "rel": "item", "href": "/api/user/:id/add-property", "methods": "PUT" });
  links.push({ "rel": "item", "href": "/api/user/property-like/:id", "methods": "PUT", "title": "Increment" });
  links.push({ "rel": "collection", "href": "/api/property", "methods": "GET,POST" });
  links.push({ "rel": "collection", "href": "/api/property/university/:text", "methods": "", "title": "Search" });
  links.push({ "rel": "item", "href": "/api/property/:id", "methods": "GET" });
  links.push({ "rel": "item", "href": "/api/property/:id", "methods": "DELETE" });
  
  const linkObject = {
    "apiName": "Web API for BTS530 Project",
    "apiDescription": "Housing web application for Students",
    "apiVersion": "1.0",
    "apiAuthor": "Soodeh Vanaki",
    "links": links
  };
  res.json(linkObject);
});



// ################################################################################
// Request handlers for data entities (listeners)

// 1. Get all
app.get('/api/user', (req, res) => {
  // Call the manager
  m.userGetAll()
    .then((data) => {
      res.json(data);
    })
    .catch((error) => {
      res.status(500).json({ 'message': error });
    })
});

// 2. Get one by identifier
app.get("/api/user/:id", (req, res) => {
  // Call the manager method
  m.userGetById(req.params.id)
    .then((data) => {
      res.json(data);
    })
    .catch(() => {
      res.status(404).json({ "message": "Resource not found" });
    })
});

// 3. Get some by last name
app.get("/api/user/name/:text", (req, res) => {
  // Call the manager method
  m.userGetByLastName(req.params.text)
    .then((data) => {
      res.json(data);
    })
    .catch(() => {
      res.status(404).json({ "message": "Resource not found" });
    })
});

// 4. Add new
app.post("/api/user", (req, res) => {
  // Call the manager method
  m.userAdd(req.body)
    .then((data) => {
      res.json(data);
    })
    .catch((error) => {
      res.status(500).json({ "message": error });
    })
});

// 5. Update existing - add a new "property"
app.put("/api/user/:id/add-property", (req, res) => {
  // Call the manager method
  m.userAddPropertyEdit(req.params.id, req.body)
    .then((data) => {
      res.json(data);
    })
    .catch(() => {
      res.status(404).json({ "message": "Resource not found" });
    })
});

// 6. Command - increment a property’s “likes” counter
// This will need an identifier parameter, and an entity body that looks like this...
// { "_id": "abc123etc." } (this is the object identifier for the property, not the user)
app.put("/api/user/property-like/:id", (req, res) => {
  // Call the manager method
  m.propertyLike(req.params.id, req.body)
    .then((data) => {
      res.json(data);
    })
    .catch(() => {
      res.status(404).json({ "message": "Resource not found" });
    })
});

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// 1. Get all
app.get('/api/property', (req, res) => {
  // Call the manager
  m.propertyGetAll()
    .then((data) => {
      res.json(data);
    })
    .catch((error) => {
      res.status(500).json({ 'message': error });
    })
});

// 2. Get one by identifier
app.get("/api/property/:id", (req, res) => {
  // Call the manager method
  m.propertyGetById(req.params.id)
    .then((data) => {
      res.json(data);
    })
    .catch(() => {
      res.status(404).json({ "message": "Resource not found" });
    })
});

// 3. Get some by university
app.get("/api/property/university/:text", (req, res) => {
  // Call the manager method
  m.propertyGetByUniversity(req.params.text)
    .then((data) => {
      res.json(data);
    })
    .catch(() => {
      res.status(404).json({ "message": "Resource not found" });
    })
});

// 4. Add new
app.post("/api/property", (req, res) => {
  // Call the manager method
  m.propertyAdd(req.body)
    .then((data) => {
      res.json(data);
    })
    .catch((error) => {
      res.status(500).json({ "message": error });
    })
});

// 5. Delete a property
app.delete("/api/property/:id", (req, res)=> {
  // Call the manager method
  m.propertyDelete(req.params.id)
    .then(() => {
      res.status(204).end();
    })
    .catch((error) => {
      res.status(404).json({ "message": error });
    })
});

// 5. Delete a user
app.delete("/api/user/:id", (req, res)=> {
  // Call the manager method
  m.userDelete(req.params.id)
    .then(() => {
      res.status(204).end();
    })
    .catch((error) => {
      res.status(404).json({ "message": error });
    })
});

// ################################################################################
// Resource not found (this should be at the end)

app.use((req, res) => {
  res.status(404).send("Resource not found");
});



// ################################################################################
// Attempt to connect to the database, and
// tell the app to start listening for requests

m.connect().then(() => {
  app.listen(HTTP_PORT, () => { console.log("Ready to handle requests on port " + HTTP_PORT) });
})
  .catch((err) => {
    console.log("Unable to start the server:\n" + err);
    process.exit();
  });