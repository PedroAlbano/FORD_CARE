var mongoose = require("mongoose");
const car_dataschema = new mongoose.Schema({
    CAR:{
        type: mongoose.mongo.ObjectID,
        required: true,
        ref: 'cars'
    },
    AIR_INTAKE_TEMP:{
        type: String,
        required: true
    },
    ENGINE_COOLANT_TEMP:{
        type: String,
        required: true
    },
    ENGINE_LOAD:{
        type: String,
        required: true
    },
    ENGINE_POWER:{
        type: String,
        required: true
    },
    ENGINE_RPM:{
        type: String,
        required: true
    },
    INTAKE_MANIFOLD_PRESSURE:{
        type: String,
        required: true
    },
    SPEED:{
        type: String,
        required: true
    },
    THROTTLE_POS:{
        type: String,
        required: true
    },
    ODOMETER:{
        type: String,
        required: true
    },
    updatedate:{
        type: Date,
        default: Date.now(),
        required: false
    }
    });

const car_data = mongoose.model("car_data", car_dataschema);
module.exports = car_data;