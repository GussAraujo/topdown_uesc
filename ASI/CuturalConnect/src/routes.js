const express = require('express');
const router = express.Router();
const { studentHandlers } = require('./handlers/student-handler');

router.post('/login', studentHandlers.login);
router.post('/register', studentHandlers.register);
 
module.exports = router;