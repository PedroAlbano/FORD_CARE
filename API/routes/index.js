var express = require('express');
const car_data = require('../models/car_data');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'FORD CARE IoT' });
});

router.post("/addcar_data",(req,res) =>{
  const {CAR,AIR_INTAKE_TEMP,ENGINE_COOLANT_TEMP,ENGINE_LOAD,ENGINE_POWER,ENGINE_RPM,INTAKE_MANIFOLD_PRESSURE,SPEED,THROTTLE_POS,ODOMETER} = req.body;
  let errors = [];

  if(!CAR || !AIR_INTAKE_TEMP || !ENGINE_COOLANT_TEMP || !ENGINE_LOAD || !ENGINE_POWER || !ENGINE_RPM || !INTAKE_MANIFOLD_PRESSURE || !SPEED || !THROTTLE_POS || !ODOMETER){
    errors.push({msg: "Sem dados"});
  }
  if(errors.lenght>0){
    res.json({Message: errors})
  }else{
    const newcar_data= new car_data({
      CAR,
      AIR_INTAKE_TEMP,
      ENGINE_COOLANT_TEMP,
      ENGINE_LOAD,
      ENGINE_POWER,
      ENGINE_RPM,
      INTAKE_MANIFOLD_PRESSURE,
      SPEED,
      THROTTLE_POS,
      ODOMETER
    });

    newcar_data
    .save()
    .then(newcar_data=>{
      res.json({ Message: "Dado do carro inserido"});
     // console.log(res);
    })
    .catch(err => console.log(err));
     }
});
module.exports = router;

router.get("/getdata/:car",(req,res) =>{
  var car = req.params.car;
  console.log(car);

  obddata.find({car: car}).exec((err, car) =>{
    console.log(car);
    res.json(car);
  })
})

/*
{
  "car" : "5f700a577504ff40d41390fc",
  "dado1" : "1234"
  "CAR" : "5f700a577504ff40d41390fc",
  "AIR_INTAKE_TEMP" : "1234",
  "ENGINE_COOLANT_TEMP" : "1234",
  "ENGINE_LOAD" : "1234",
  "ENGINE_POWER" : "1234",
  "ENGINE_RPM" : "1234",
  "INTAKE_MANIFOLD_PRESSURE" : "1234",
  "SPEED" : "1234",
  "THROTTLE_POS" : "1234",
  "ODOMETER" : 10000;
}
*/