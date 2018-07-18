const express = require('express');
const app = express();
const bodyParser = require('body-parser');
var db = require('./database/db');
const fs = require('fs');
const readline = require('readline');
const async = require('async');


//port setting
var port = 3000;

//middleware
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended: false}));

//static content, such as stylesheet, images, etc.
app.use(express.static(__dirname + '/public'));

//template engine
app.set('view engine', 'ejs');
app.set('views', __dirname + '/views');

//various app data ** TEMPORARY, this data will be fetched from db **
var data = require('./dummy.json');

//routes
app.get('/', (req, res) => {
    db.query(`SELECT * FROM my_data`, (err, rows) => {
        console.log(rows);
        res.render('main', {datas: rows});
    });
});

//infinite async loop which reads from log file and store data in db
const delay = 1000;

async.forever(
(next) => {

    fs.readFile('logfile', function(err, datas) {
        if(err) throw err;
        var array = datas.toString().split("\n");
        for(i in array) {
            if (array[i]){
                db.query(`INSERT INTO my_data VALUES (null, "${array[i]}", null)`);
                console.log(array[i]);
            }
        }
        
        fs.writeFile('./logfile', '', function(){});
        
    });

    setTimeout(next, delay);
}, 

(err) => {
    console.log(err);
});


//start server
app.listen(port, () => {
    console.log(`Server listening on ${port}`);
})