// #######################
// Soodeh Vanaki
// Fall 2020 - BTS530
// Housing Api
// #######################
// ################################################################################
// Data service operations setup

const mongoose = require('mongoose');
mongoose.set('useNewUrlParser', true);
mongoose.set('useFindAndModify', false);
mongoose.set('useCreateIndex', true);

// Load the schemas...

// Data entities; the standard format is:
const user = require('./msc-user');
const property = require('./msc-property');
const type = require('./msc-type');
const userSchema = require('./msc-user');
const propertySchema = require('./msc-property');
const typeSchema = require('./msc-type');

// ################################################################################
// Define the functions that can be called by server.js

module.exports = function () {

  // Collection properties, which get their values upon connecting to the database
  let user;
  let property;
  let type;
  
  return {

    // ############################################################
    // Connect to the database

    connect: function () {
      return new Promise(function (resolve, reject) {

        // Create connection to the database
        console.log('Attempting to connect to the database...');

        // The following works for localhost...
        // Replace the database name with your own value
        // mongoose.connect('mongodb://localhost:27017/testing', { connectTimeoutMS: 5000, useUnifiedTopology: true });
        mongoose.connect('mongodb+srv://dbUser1:dbUser1password@cluster0-hrd8t.mongodb.net/test?retryWrites=true&w=majority', { dbName: 'BTS530', connectTimeoutMS: 5000, useUnifiedTopology: true });

        // This one works for MongoDB Atlas...
        // (coming soon)

        // From https://mongoosejs.com/docs/connections.html
        // Mongoose creates a default connection when you call mongoose.connect(). 
        // You can access the default connection using mongoose.connection.
        var db = mongoose.connection;

        // Handle connection events...
        // https://mongoosejs.com/docs/connections.html#connection-events
        // The data type of a connection event is string
        // And more than one connection event may be emitted during execution

        // FYI the Node.js EventEmitter class docs is here...
        // https://nodejs.org/api/events.html#events_class_eventemitter

        // Handle the unable to connect scenario
        // "on" is a Node.js method in the EventEmitter class
        // https://nodejs.org/api/events.html#events_emitter_on_eventname_listener
        db.on('error', (error) => {
          console.log('Connection error:', error.message);
          reject(error);
        });

        // Handle the open/connected event scenario
        // "once" is a Node.js method in the EventEmitter class
        // https://nodejs.org/api/events.html#events_emitter_once_eventname_listener
        db.once('open', () => {
          console.log('Connection to the database was successful');
          user = db.model("user", userSchema, "user");
          property = db.model("property", propertySchema, "property");
          type = db.model("type", typeSchema, "type");

          resolve();
        });
      });
    },



    // ############################################################
    
     userGetAll: function () {
      return new Promise((resolve, reject) => {

        user.find()
          .sort({ last_name: 'asc' })
          .exec((error, items) => {
            if (error) {
              // Query error
              return reject(error.message);
            }
            // Found, a collection will be returned
            return resolve(items);
          });
      });
    },

    userGetById: function (itemId) {
      return new Promise(function (resolve, reject) {

        // Find one specific document
        user.findById(itemId)
          .exec((error, item) => {
            if (error) {
              // Find/match is not found
              return reject(error.message);
            }
            // Check for an item
            if (item) {
              // Found, one object will be returned
              return resolve(item);
            } else {
              return reject('Not found');
            }
          });
      })
    },

    userGetByLastName: async function (text) {

      // URL decode the incoming value
      text = decodeURIComponent(text);

      // Attempt to find in the "name" field, case-insensitive
      let results = await user.find({ last_name: { $regex: text, $options: "i" } });
      // This will find zero or more
      return results;
    },

    userAdd: async function (newItem) {

      // Attempt to create a new item
      let newUser = new user(newItem);

      if (newUser) {
        // Save
        await newUser.save();
        return newUser;
      }
      else {
        // Uh oh, "throw" an error
        throw "Not found";
      }
    },

    // This will need a property that looks like this...
    // {street_address":"1043 Thierer Pass","city":"Cabano","province":"Québec","country":"Canada","image":"http://dummyimage.com/195x111.png/cc0000/ffffff","unversity":"Laurentian University of Sudbury","available_date":"12/18/2019","price":590.39,"number_of_bedrooms":3,"number_of_bathrooms":3,"kitchen":true,"parking":false},
    userAddPropertyEdit: async function (userId, newItem) {

      // Attempt to locate the existing document
      let userFound = await user.findById(userId);

      if (userFound) {
        // Add the new property and save
        userFound.property.push(newItem);
        await userFound.save();
        return userFound;
      }
      else {
        // Uh oh, "throw" an error
        throw "Not found";
      }
    },

    // Command - increment a property’s “likes” counter
    // This will need an identifier parameter, and an entity body that looks like this...
    // { "_id": "abc123etc." } (this is the object identifier for the property, not the user)
    propertyLike: async function (itemId, newItem) {

      // Early exit, confirm that the parameter and entity body match
      if (itemId !== newItem._id) {
        // Uh oh, "throw" an error
        throw "Not found";
      }

      // Attempt to locate the existing property that has the desired user
      let term = await user.findOne({ "user.property._id": itemId });

      if (term) {
       // Attempt to locate the definition
        let def = term.property.id(itemId);
        // Increment and save
        def.likes++;
        await term.save();
        // Send the entire property back to the requestor
        return term;
      }
      else {
        // Uh oh, "throw" an error
        throw "Not found";
      }
    },
    
    propertyGetAll: function () {
      return new Promise((resolve, reject) => {

        property.find()
          .sort({ price: 'asc' })
          .exec((error, items) => {
            if (error) {
              // Query error
              return reject(error.message);
            }
            // Found, a collection will be returned
            return resolve(items);
          });
      });
    },

    propertyGetById: function (itemId) {
      return new Promise(function (resolve, reject) {

        // Find one specific property
        property.findById(itemId)
            .exec((error, item) => {
            if (error) {
              // Find/match is not found
              return reject(error.message);
            }
            // Check for a property
            if (item) {
              // Found, one object will be returned
              return resolve(item);
            } else {
              return reject('Not found');
            }
          });
      })
    },

  // Must send a property entity that includes a user identifier
    propertyAdd: async function(newItem) {

      // Attempt to locate the existing user
      //let user = await user.findById(newItem.userId);
        let newProperty = new property(newItem);
      if (newProperty) {
        
        // We can continue
        //let property = new property(newItem);
        await newProperty.save();
        return newProperty;
      }
      else {
        // Uh oh, "throw" an error
        throw "Not found";
      }
    },
  
    propertyGetByUniversity: async function (text) {

    // URL decode the incoming value
    text = decodeURIComponent(text);

    // Attempt to find in the "university" field, case-insensitive
    let results = await property.find({ university: { $regex: text, $options: "i" } });
    // This will find zero or more
    return results;
    },

    propertyDelete: async function (itemId) {
      return new Promise(function (resolve, reject) {

        property.findByIdAndRemove(itemId, (error) => {
          if (error) {
            // Cannot delete item
            return reject(error.message);
          }
          // Return success, but don't leak info
          return resolve();
        })
      })
    },

    userDelete: async function (userId) {
      return new Promise(function (resolve, reject) {

        user.findByIdAndRemove(userId, (error) => {
          if (error) {
            // Cannot delete item
            return reject(error.message);
          }
          // Return success, but don't leak info
          return resolve();
        })
      })  
    },

    userLogin: async function (userinfo) {
      return new Promise((resolve, reject) => {
        user.find({email: userinfo.email}).limit(1)
        .exec((error, item) => {
          if (error) {
            // Find/match is not found
            return reject(error.message);
          }
          // Check for an item
          if (item) {
            // Found, one object will be returned
            if (item[0].password == userinfo.password) {
              return resolve({
                "message":"SUCCESS",
                "user": item[0]
              });
            } else {
              return resolve({
                "message":"FAIL"
              });
            }
          } else {
            return reject('Not found');
          }
        });
      });
    }
  } 
}