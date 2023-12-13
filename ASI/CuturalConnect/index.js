const express = require('express')
const app = express()
const cors = require('cors');
const routes = require('./src/routes');
const { mongodb } = require('./src/db');

mongodb.connect()

try {
  app.use(express.json());
  app.use(cors());

  app.use('/', routes);

  app.listen(3001, () => {
    console.log('Server on port 3001...')
  })
} catch (error) {
  throw new Error(error.message)
}