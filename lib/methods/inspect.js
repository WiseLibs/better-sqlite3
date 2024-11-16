const DatabaseInspection = function Database() {
};

export default function inspect(depth, opts) {
	return Object.assign(new DatabaseInspection(), this);
}

