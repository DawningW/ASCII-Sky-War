package controller

import (
	"famehall/database"
	"famehall/service"
)

var Db = database.DB
var HallService = service.NewHall()
