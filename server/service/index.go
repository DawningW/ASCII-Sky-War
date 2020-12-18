package service

import (
	"famehall/database"
)

// NewHall get a Hall service
func NewHall() ScoreService {
	return ScoreService{
		db: database.DB,
	}
}
