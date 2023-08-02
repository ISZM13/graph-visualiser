const express = require('express');
const fs = require('fs');
const app = express();
const port = 3000;

app.use(express.json());
app.use(express.urlencoded({ extended: true }));

app.post('/submit-data', (req, res) => {
  const data = req.body;

  // Read existing data from the JSON file (if it exists)
  let jsonData = [];
  try {
    const existingData = fs.readFileSync('data.json', 'utf8');
    jsonData = JSON.parse(existingData);
  } catch (err) {
    console.error('Error reading existing data or file not found:', err);
  }

  // Add the new data to the existing data
  jsonData.push(data);

  // Write the updated data back to the JSON file
  try {
    fs.writeFileSync('data.json', JSON.stringify(jsonData, null, 2), 'utf8');
    console.log('Data has been written to data.json');
    res.status(200).send('Data has been written to data.json');
  } catch (err) {
    console.error('Error writing data to file:', err);
    res.status(500).send('Error writing data to file');
  }
});

app.listen(port, () => {
  console.log(`Server is running on http://localhost:${port}`);
});
