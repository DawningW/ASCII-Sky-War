package reso

// GetHall GET "/hall" response object
type GetHall struct {
	ID    int64  `json:"id"`
	Name  string `json:"name"`
	Score int64  `json:"score"`
	Time  int64  `json:"time"`
	Rank  int64  `json:"rank"`
	Total int64  `json:"total"`
}

// PostHall POST "/hall" response object
type PostHall struct {
	ID int64 `json:"id"`
}
