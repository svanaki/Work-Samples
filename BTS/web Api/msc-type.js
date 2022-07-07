// #######################
// Soodeh Vanaki
// Fall 2020 - BTS530
// Housing Api
// #######################
// Setup
var mongoose = require('mongoose');
var Schema = mongoose.Schema;

// Entity schema
var typeSchema = new Schema({
    student: Boolean,
    landlord: Boolean
});
//var typeSchema = {student, landlord};
// Make schema available to the application
module.exports = typeSchema;