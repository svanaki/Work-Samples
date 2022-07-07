// #######################
// Soodeh Vanaki
// Fall 2020 - BTS530
// Housing Api
// #######################
// Setup
var mongoose = require('mongoose');
var Schema = mongoose.Schema;

// Entity schema
var propertySchema = new Schema({
  street_address: String,
  city: String, 
  province: String, 
  country: String,
  image: String,
  university: String,
  available_date: Date,
  price: Number,
  number_of_bedrooms: Number,
  number_of_bathrooms: Number,
  kitchen: Boolean,
  parking: Boolean
});

// Make schema available to the application
module.exports = propertySchema;