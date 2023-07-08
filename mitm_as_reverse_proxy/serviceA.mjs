import express from "express";
import fetch from "node-fetch";

const app = express();

app.get("/", async function (req, res){
  const r = await fetch("http://localhost:6001/");
  const result = await r.text();
  return res.send(result);
});

app.listen(6793, () => {
  console.log("Service A on 6793");
});