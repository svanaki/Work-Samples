// #######################
// Soodeh Vanaki
// Fall 2020 - BTS530
// Housing Api
// #######################
// Setup
var mongoose = require('mongoose');
const propertySchema = require('./msc-property');
const typeSchema = require('./msc-type');
var Schema = mongoose.Schema;

// Entity schema
var userSchema = new Schema({
  first_name: String,
  last_name: String,
  email: String,
  phone_number: Number,
  street_address: String,
  city: String, 
  province: String, 
  country: String,
  type: [typeSchema], 
  property_info: [propertySchema],

  username: String,
  password: String
});

// Make schema available to the application
module.exports = userSchema;