import express from "express";

const app = express();

app.get("/", (req, res) => res.send("Hello from service B."));

app.listen(6002, () => {
  console.log("Service A on 6002");
});