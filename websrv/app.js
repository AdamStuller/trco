const express = require('express')
const bodyParser = require('body-parser')
const app = express();
const data = require(__dirname + '/dummy.json');

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

app.get('/', (req, res) => {
    res.render('index', data);
})

app.get('/logfile', (req, res) => {
    res.render('data');
})


app.listen(port, () => {
    console.log(`Server listening on ${port}`);
    // console.log();
})