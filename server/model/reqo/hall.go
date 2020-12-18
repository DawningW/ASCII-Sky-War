package reqo

// GetHall GET "/hall" request object
type GetHall struct {
	ID     int64  `json:"id"`
	Name   string `json:"name"`
	Record int64  `json:"record"`
}

// PostHall POST "/hall" request object
type PostHall struct {
	Name  string `json:"name"`
	Score int64  `json:"score"`
}
