const express = require('express');
const router = express.Router();
const { studentHandlers } = require('./handlers/student-handler');

try {
  router.post('/login', studentHandlers.login);
  router.post('/register', studentHandlers.register); 
} catch (error) {
  throw new Error(error.message)
}

module.exports = router;