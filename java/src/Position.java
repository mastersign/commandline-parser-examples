/**
 * Beschreibt eine 2-dimensionale Position.
 */
class Position {

    public double x;
    public double y;

    public Position(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public Position(Position p) {
        this.x = p.x;
        this.y = p.y;
    }

    public String toString() {
        return String.format("(%.1f; %.1f)", x, y);
    }
}
